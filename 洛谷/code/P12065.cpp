#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;
const int INF = 2e18;

int n,q,K,P;

int x[MAXN];
int y[MAXN];

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

priority_queue<long double>heap;

long double ans[MAXN];

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

// 计算 |v|^K
long double powerK(int v){
    long double a=fabsl((long double)v);

    if(K==1){
        return a;
    }
    if(K==2){
        return a*a;
    }
    if(K==3){
        return a*a*a;
    }

    long double res=1;
    int p=K;
    while(p){
        if(p&1){
            res*=a;
        }
        a*=a;
        p>>=1;
    }
    return res;
}

// 点i到询问点(qx,qy)的K次方距离
// 查询过程中不开根，因为开根不影响大小关系
long double dist(int qx,int qy,int i){
    return powerK(qx-x[i])+powerK(qy-y[i]);
}

// 查询点(qx,qy)到i子树包围盒的最小K次方距离
long double guess(int qx,int qy,int i){
    if(i==0){
        return numeric_limits<long double>::infinity();
    }

    int dx=0;
    int dy=0;

    if(qx<xmin[i]){
        dx=xmin[i]-qx;
    }
    else if(qx>xmax[i]){
        dx=qx-xmax[i];
    }

    if(qy<ymin[i]){
        dy=ymin[i]-qy;
    }
    else if(qy>ymax[i]){
        dy=qy-ymax[i];
    }

    return powerK(dx)+powerK(dy);
}

// 查询距离(qx,qy)最近的P个点
void updateAns(int qx,int qy,int i){
    if(i==0){
        return ;
    }

    // 当前点尝试进入答案
    heap.push(dist(qx,qy,i));

    if((int)heap.size()>P){
        heap.pop();
    }

    // 左右子树理论上的最小距离
    long double gl=guess(qx,qy,ls[i]);
    long double gr=guess(qx,qy,rs[i]);

    // 优先搜索更近的子树
    if(gl<gr){
        if((int)heap.size()<P||gl<heap.top()){
            updateAns(qx,qy,ls[i]);
        }
        if((int)heap.size()<P||gr<heap.top()){
            updateAns(qx,qy,rs[i]);
        }
    }
    else{
        if((int)heap.size()<P||gr<heap.top()){
            updateAns(qx,qy,rs[i]);
        }
        if((int)heap.size()<P||gl<heap.top()){
            updateAns(qx,qy,ls[i]);
        }
    }
}

// 将K次方距离恢复成真实距离
long double realDist(long double d){
    if(K==1){
        return d;
    }
    if(K==2){
        return sqrtl(d);
    }
    if(K==3){
        return cbrtl(d);
    }
    return powl(d,1.0L/K);
}

signed main()
{
    cin>>n>>q>>K>>P;
    xmin[0]=ymin[0]=INF;
    xmax[0]=ymax[0]=-INF;

    cntkdt=n;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
        ls[i]=rs[i]=0;
        sz[i]=1;
        xmin[i]=xmax[i]=x[i];
        ymin[i]=ymax[i]=y[i];
        arr[i]=i;
    }
    root=build(1,n,0);
    
    cout<<fixed<<setprecision(4);

    for(int i=1;i<=q;i++){
        char op;
        int qx,qy;
        cin>>op>>qx>>qy;
        if(op=='A'){
            add(qx,qy);
        }
        else{
            while(!heap.empty()){
                heap.pop();
            }
            updateAns(qx,qy,root);
            for(int j=P;j>=1;j--){
                ans[j]=heap.top();
                heap.pop();
            }
            for(int j=1;j<=P;j++){
                if(j>1){
                    cout<<' ';
                }
                cout<<realDist(ans[j]);
            }

            cout<<'\n';
        }
    }
    return 0;
}