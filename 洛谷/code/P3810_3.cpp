// 三维偏序，C++版
// 本题就是讲解170，题目1，讲了CDQ分治的解法，这里用kdt的解法
// 一共有n个对象，每个对象有a、b、c三个属性，每个属性值的范围都是[1, k]
// f(i)表示，aj <= ai 且 bj <= bi 且 cj <= ci 且 j != i 的j的数量
// ans(d)表示，f(i) == d 的i的数量
// 打印所有的ans[d]，d的范围[0, n)
// 1 <= n <= 10^5
// 1 <= k <= 2 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P3810
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int INF = 1e9;

int n,k;

struct node{
    int a,x,y;
};
bool acmp(node &a,node &b){
    return a.a<b.a;
}

node nums[MAXN];

// K-D树的节点计数
int cntkdt;

// K-D树采用替罪羊树的方式，只有一个头
int root;
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
int xmin[MAXN];
int xmax[MAXN];
int ymin[MAXN];
int ymax[MAXN];
int x[MAXN];
int y[MAXN];

int ans[MAXN];

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
    sz[cntkdt]=1;
    xmin[cntkdt]=xmax[cntkdt]=qx;
    ymin[cntkdt]=ymax[cntkdt]=qy;
    return cntkdt;
}

int compare(int i,int j,int dimension){
    int v1=dimension==0?x[i]:y[i];
    int v2=dimension==0?x[j]:y[j];
    return v1==v2?0:v1<v2?-1:1;
}

struct cmp{
    int dimension;
    bool operator()(int a,int b)const{
        return compare(a,b,dimension)<0;
    }
};

void maintain(int i){
    sz[i]=sz[ls[i]]+sz[rs[i]]+1;
    xmin[i]=min(x[i],min(xmin[ls[i]],xmin[rs[i]]));
    xmax[i]=max(x[i],max(xmax[ls[i]],xmax[rs[i]]));
    ymin[i]=min(y[i],min(ymin[ls[i]],ymin[rs[i]]));
    ymax[i]=max(y[i],max(ymax[ls[i]],ymax[rs[i]]));
}

bool balance(int i){
    return ALPHA*sz[i]>=max(sz[ls[i]],sz[rs[i]]);
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
    if(u){
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

// 目前来到了u  它的父亲是fa  是fa的side儿子，维度是dimension
int add(int insertNode,int u,int fa,int side,int dimension){
    if(u==0){
        return insertNode;
    }
    if(compare(insertNode,u,dimension)<=0){
        ls[u]=add(insertNode,ls[u],u,1,dimension^1);
    }
    else{
        rs[u]=add(insertNode,rs[u],u,2,dimension^1);
    }
    maintain(u);
    if(!balance(u)){
        top=u;
        topFather=fa;
        topDimension=dimension;
        topSide=side;
    }
    return u;
}

// 插入一个qx qy qv的节点
void add(int qx,int qy){
    // 可能会导致不平衡 所以提前设置一下
    top=topFather=topSide=topDimension=0;
    // 初始化一个kd树节点
    int insertnode=init(qx,qy);
    root=add(insertnode,root,0,0,0);
    rebuild();
}

// 目前来到了i，需要查询范围是x1 y1到x2 y2范围的权值和
int query(int qx,int qy,int i){
    if(i==0){
        return 0;
    }
    if(xmin[i]>qx||ymin[i]>qy){
        return 0;
    }
    if(xmax[i]<=qx&&ymax[i]<=qy){
        return sz[i];
    }
    int ans=0;
    if(x[i]<=qx&&y[i]<=qy){
        ans++;
    }
    ans+=query(qx,qy,ls[i]);
    ans+=query(qx,qy,rs[i]);
    return ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>nums[i].a>>nums[i].x>>nums[i].y;
    }
    sort(nums+1,nums+n+1,acmp);

    xmin[0]=ymin[0]=INF;
    xmax[0]=ymax[0]=-INF;

    for(int l=1,r=1;l<=n;l=++r){
        while(r+1<=n&&nums[r+1].a==nums[l].a){
            r++;
        }
        for(int i=l;i<=r;i++){
            add(nums[i].x,nums[i].y);
        }
        for(int i=l;i<=r;i++){
            int fi=query(nums[i].x,nums[i].y,root)-1;
            ans[fi]++;
        }
    }
    for(int d=0;d<n;d++){
        cout<<ans[d]<<endl;
    }
    return 0;
}