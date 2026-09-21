// 射击场，C++版
// 每个靶子是一个矩形区域，x轴的范围[l, r]，y轴的范围[d, u]，还有z轴的数值
// 空间里有n个靶子，接下来有m发子弹，每发子弹给定出发时的x和y坐标，子弹沿z轴前进
// 子弹会击中前进过程中遇到的第一个尚未消失的靶子，随后击中的靶子和这发子弹都消失
// 对于每一发子弹，打印它击中的靶子编号，如果没有击中打印0
// 1 <= n、m <= 10^5
// 0 <= 坐标值 <= 10^7
// 测试链接 : https://www.luogu.com.cn/problem/CF44G
// 测试链接 : https://codeforces.com/problemset/problem/44/G
// 这道题的大思路是将靶子按照先后顺序进行排列
// 将子弹建立KD树，相当于靶子选走子弹 然后再KD树中删除这个子弹
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int INF = 2e9;

int n,m;

// 靶子的结构体信息
struct node{
    int l,r,d,u,z,id;
};
bool zcmp(node &a,node &b){
    return a.z<b.z;
}
node nums[MAXN];

// 子弹的信息  用于建立KD树
int x[MAXN];
int y[MAXN];

// K-D树的节点计数
int cntkdt;

// K-D树采用替罪羊树的方式，只有一个头
// 维护区间最小的子弹编号 因为这个子弹会先发射
int root;
int ls[MAXN];
int rs[MAXN];
int idmin[MAXN];
int xmin[MAXN];
int xmax[MAXN];
int ymin[MAXN];
int ymax[MAXN];

int bullet;
int ans[MAXN];

// 这个用于判断这个节点是不是删除了
// 另外一个记录这个区间范围有多少个点还没有被删除
bool alive[MAXN];
int alivesz[MAXN];

// 替罪羊树平衡因子
double ALPHA = 0.7;
// 这些信息都是为了处理不平衡时的重构操作
// 最上方的不平衡点
int top;
// 不平衡点的父亲
int topFather;
// 这个不平衡点在他父亲的那一边
int topSide;
// 最顶部不平衡点用什么维度进行的划分
int topDimension;
// 不平衡时收集节点编号
int arr[MAXN];
// 遍历不平衡子树，收集到的节点数量
int treeSiz;

// 初始化一个KD树节点
int init(int qx,int qy){
    cntkdt++;
    x[cntkdt]=qx;
    y[cntkdt]=qy;
    ls[cntkdt]=rs[cntkdt]=0;
    alive[cntkdt]=true;
    alivesz[cntkdt]=1;
    xmin[cntkdt]=xmax[cntkdt]=qx;
    ymin[cntkdt]=ymax[cntkdt]=qy;
    idmin[cntkdt]=cntkdt;
    return cntkdt;
}

// 这里的compare函数写起来是有讲究的
// 我们是按照编号来判断的 也就是找到唯一一个编号为id的
// 因为需要如果两个点的xy相同,那么必须要比较编号
int compare(int i,int j,int dimension){
    int v1=dimension==0?x[i]:y[i];
    int v2=dimension==0?x[j]:y[j];
    return v1 != v2 ? (v1 < v2 ? -1 : 1) : (i - j);
}

struct cmp{
    int dimension;
    bool operator()(int a,int b)const{
        return compare(a,b,dimension)<0;
    }
};

void maintain(int i){
    int l=ls[i],r=rs[i];
    if(alive[i]){
        alivesz[i]=1+alivesz[l]+alivesz[r];
        xmin[i]=xmax[i]=x[i];
        ymin[i]=ymax[i]=y[i];
        idmin[i]=i;
    }
    else{
        alivesz[i]=alivesz[l]+alivesz[r];
        xmin[i]=ymin[i]=INF;
        xmax[i]=ymax[i]=-INF;
        idmin[i]=INF;
    }
    if (alivesz[l] != 0) {
        xmin[i] = min(xmin[i], xmin[l]);
        xmax[i] = max(xmax[i], xmax[l]);
        ymin[i] = min(ymin[i], ymin[l]);
        ymax[i] = max(ymax[i], ymax[l]);
        idmin[i] = min(idmin[i], idmin[l]);
    }
    if (alivesz[r] != 0) {
        xmin[i] = min(xmin[i], xmin[r]);
        xmax[i] = max(xmax[i], xmax[r]);
        ymin[i] = min(ymin[i], ymin[r]);
        ymax[i] = max(ymax[i], ymax[r]);
        idmin[i] = min(idmin[i], idmin[r]);
    }
}

bool balance(int i){
    return ALPHA*alivesz[i]>=max(alivesz[ls[i]],alivesz[rs[i]]);
}

// 将编号范围为l到r的点按照dimension维度排序
int build(int l,int r,int dimension){
    if(l>r){
        return 0;
    }
    int mid=(l+r)>>1;
    // 在区间arr[l ... r]中，参数分别是l mid  r+1
    // 按照 Cmp{dimension} 这个比较规则，把第 mid-l+1 小的元素放到 arr[mid]
    // mid前面的小于它  mid后面的大于它
    nth_element(arr+l,arr+mid,arr+r+1,cmp{dimension});
    int rt=arr[mid];
    ls[rt]=build(l,mid-1,dimension^1);
    rs[rt]=build(mid+1,r,dimension^1);
    maintain(rt);
    return rt;
}

// 收集整个不平衡子树  准备重构
void dfs(int u){
    if(u&&alivesz[u]!=0){
        if(alive[u])
            arr[++treeSiz]=u;
        dfs(ls[u]);
        dfs(rs[u]);
    }
}

// 对不平衡的替罪羊树部分进行调整
void rebuild(){
    if(top!=0){
        treeSiz=0;
        dfs(top);
        int newRoot=build(1,treeSiz,topDimension);
        if(topFather==0){
            root=newRoot;
        }
        else if(topSide==1){
            ls[topFather]=newRoot;
        }
        else{
            rs[topFather]=newRoot;
        }
    }
}

int add(int insertnode,int u,int fa,int side,int dimension){
    if(u==0||alivesz[u]==0){
        return insertnode;
    }
    if(compare(insertnode,u,dimension)<=0){
        ls[u]=add(insertnode,ls[u],u,1,dimension^1);
    }
    else{
        rs[u]=add(insertnode,rs[u],u,2,dimension^1);
    }
    maintain(u);
    if(!balance(u)){
        top=u;
        topFather=fa;
        topSide=side;
        topDimension=dimension;
    }
    return u;
}

void add(int qx,int qy){
    top=topFather=topDimension=topSide=0;
    int insertnode=init(qx,qy);
    root=add(insertnode,root,0,0,0);
    rebuild();
}

void remove(int removenode,int u,int fa,int side,int dimension){
    if(u==removenode){
        alive[u]=false;
    }
    else if(compare(removenode,u,dimension)<=0){
        remove(removenode,ls[u],u,1,dimension^1);
    }
    else{
        remove(removenode,rs[u],u,2,dimension^1);
    }
    maintain(u);
    if(!balance(u)){
        top=u;
        topFather=fa;
        topSide=side;
        topDimension=dimension;
    }
}

void remove(int removenode){
    top=topFather=topDimension=topSide=0;
    remove(removenode,root,0,0,0);
    rebuild();
}

void query(int ql,int qr,int qd,int qu,int i){
    if(i==0||alivesz[i]==0||idmin[i]>bullet){
        return;
    }
    if(xmax[i]<ql||xmin[i]>qr||ymax[i]<qd||ymin[i]>qu){
        return ;
    }
    if(ql<=xmin[i]&&qr>=xmax[i]&&qd<=ymin[i]&&qu>=ymax[i]){
        bullet=min(bullet,idmin[i]);
        return ;
    }
    if(alive[i]&&ql<=x[i]&&qr>=x[i]&&qd<=y[i]&&qu>=y[i]){
        bullet=min(bullet,i);
    }
    int l=ls[i];
    int r=rs[i];
    if(idmin[l]<=idmin[r]){
        query(ql,qr,qd,qu,l);
        query(ql,qr,qd,qu,r);
    }
    else{
        query(ql,qr,qd,qu,r);
        query(ql,qr,qd,qu,l);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].l>>nums[i].r>>nums[i].d>>nums[i].u>>nums[i].z;
        nums[i].id=i;
    }
    sort(nums+1,nums+n+1,zcmp);
    xmin[0]=ymin[0]=INF;
    xmax[0]=ymax[0]=-INF;
    idmin[0]=INF;

    cin>>m;
    for(int i=1;i<=m;i++){
        int qx,qy;
        cin>>qx>>qy;
        // 因为这里的编号从1开始增加
        // 恰好是这个子弹的顺序  所以不需要多一个参数
        add(qx,qy);
    }

    for(int i=1;i<=n;i++){
        bullet=INF;
        query(nums[i].l,nums[i].r,nums[i].d,nums[i].u,root);
        if(bullet!=INF){
            ans[bullet]=nums[i].id;
            remove(bullet);
        }
    }
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}