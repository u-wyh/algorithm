// 天使玩偶，C++版
// 本题就是讲解170，题目6，讲了CDQ分治的解法，这里用kdt的解法
// 规定(x1, y1)和(x2, y2)之间的距离 = | x1 - x2 | + | y1 - y2 |
// 一开始先给定n个点的位置，接下来有m条操作，每种操作是如下两种类型中的一种
// 操作 1 x y : 在(x, y)位置添加一个点
// 操作 2 x y : 打印已经添加的所有点中，距离(x, y)最近的点有多远
// 1 <= n、m <= 3 * 10^5
// 0 <= x、y <= 10^6
// 测试链接 : https://www.luogu.com.cn/problem/P4169
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 6e5+5;
const int INF = 2e18;

int n,m;
int x[MAXN];
int y[MAXN];

int cntkdt;
int root;
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
int sum[MAXN];
int xmin[MAXN];
int xmax[MAXN];
int ymin[MAXN];
int ymax[MAXN];

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

int ans;

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

int guess(int qx,int qy,int i){
    if (i == 0) {
        return INF;
    }
    int ans = qx < xmin[i] ? xmin[i] - qx : qx > xmax[i] ? qx - xmax[i] : 0;
    ans += qy < ymin[i] ? ymin[i] - qy : qy > ymax[i] ? qy - ymax[i] : 0;
    return ans;
}

void updateAns(int qx,int qy,int i){
    if(i==0){
        return ;
    }
    ans=min(ans,abs(qx-x[i])+abs(qy-y[i]));
    int gl=guess(qx,qy,ls[i]);
    int gr=guess(qx,qy,rs[i]);
    if(gl<gr){
        if(gl<ans){
            updateAns(qx,qy,ls[i]);
        }
        if(gr<ans){
            updateAns(qx,qy,rs[i]);
        }
    }
    else{
        if(gr<ans){
            updateAns(qx,qy,rs[i]);
        }
        if(gl<ans){
            updateAns(qx,qy,ls[i]);
        }
    }
}

signed main()
{
    cin>>n>>m;
    xmin[0]=ymin[0]=INF;
    xmax[0]=ymax[0]=-INF;
    for(int i=1;i<=n;i++){
        int qx,qy;
        cin>>qx>>qy;
        add(qx,qy);
    }
    for(int i=1,op,qx,qy;i<=m;i++){
        cin>>op>>qx>>qy;
        if(op==1){
            add(qx,qy);
        }
        else{
            ans=INF;
            updateAns(qx,qy,root);
            cout<<ans<<endl;
        }
    }
    return 0;
}