// 简单题，替罪羊树的方式，C++版
// 有一个n * n的平面区域，初始时没有点，有若干条操作，类型如下
// 操作 1 a b c   : 平面里增加一个点，坐标(a, b)，点权为c
// 操作 2 a b c d : 查询(a, b)为左下角、(c, d)为右上角的区域中，所有点的点权和
// 操作 3         : 终止，以后没有操作了
// 本题要求强制在线，得到操作参数的规则，打开测试链接查看
// 1 <= n <= 5 * 10^5
// 操作数不超过2e5
// 测试链接 : https://www.luogu.com.cn/problem/P4148
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int INF = 2e18;

int n;

int x[MAXN];
int y[MAXN];
int v[MAXN];

// K-D树的节点计数
int cntkdt;

// K-D树采用替罪羊树的方式，只有一个头
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

// 初始化一个KD树节点
int init(int qx,int qy,int qv){
    cntkdt++;
    x[cntkdt]=qx;
    y[cntkdt]=qy;
    v[cntkdt]=qv;
    ls[cntkdt]=rs[cntkdt]=0;
    sz[cntkdt]=1;
    sum[cntkdt]=qv;
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
    sum[i]=sum[ls[i]]+sum[rs[i]]+v[i];
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
void add(int qx,int qy,int qv){
    // 可能会导致不平衡 所以提前设置一下
    top=topFather=topSide=topDimension=0;
    // 初始化一个kd树节点
    int insertnode=init(qx,qy,qv);
    root=add(insertnode,root,0,0,0);
    rebuild();
}

int query(int x1,int y1,int x2,int y2,int i){
    if(i==0){
        return 0;
    }
    if(xmax[i]<x1||xmin[i]>x2||ymax[i]<y1||ymin[i]>y2){
        return 0;
    }
    if(x1<=xmin[i]&&xmax[i]<=x2&&y1<=ymin[i]&&ymax[i]<=y2){
        return sum[i];
    }
    int ans=0;
    if(x1<=x[i]&&x[i]<=x2&&y1<=y[i]&&y[i]<=y2){
        ans+=v[i];
    }
    ans+=query(x1,y1,x2,y2,ls[i]);
    ans+=query(x1,y1,x2,y2,rs[i]);
    return ans;
}

int query(int x1,int y1,int x2,int y2){
    return query(x1,y1,x2,y2,root);
}

signed main()
{
    cin>>n;
    xmin[0]=ymin[0]=INF;
    xmax[0]=ymax[0]=-INF;

    int op,a,b,c,d,lastans;
    cin>>op;
    lastans=0;
    while(op!=3){
        cin>>a>>b>>c;
        a^=lastans;
        b^=lastans;
        c^=lastans;
        if(op==1){
            add(a,b,c);
        }
        else{
            cin>>d;
            d^=lastans;
            lastans=query(a,b,c,d);
            cout<<lastans<<endl;
        }
        cin>>op;
    }
    return 0;
}