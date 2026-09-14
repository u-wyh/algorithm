// K-D树结合懒更新，替罪羊树的方式，C++版
// 点的坐标有k维，点还有点权，k维空间中的轴对齐区域，可以用两个对角点表示
// 一共有m条操作，类型如下
// 操作 1 qx qv    : 空间里增加一个点，qx是k个值表示点的坐标，qv表示点权
// 操作 2 qx qy qv : 区域的两个对角点qx和qy，各自有k个值的坐标，该区域所有点的点权增加qv
// 操作 3 qx qy    : 区域的两个对角点qx和qy，各自有k个值的坐标，打印该区域所有点的点权和
// 本题要求强制在线，得到操作参数的规则，打开测试链接查看
// 2 <= k <= 3
// 1 <= m <= 10^5
// 坐标、点权、答案都需要long类型
// 测试链接 : https://www.luogu.com.cn/problem/P14312
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int MAXK = 3;
const int INF = 2e18;

int k,m;

// 这个是点的位置信息
int pos[MAXN][MAXK];
int val[MAXN];
// 这个其实是输入的点的编号信息
int qx[MAXK];
int qy[MAXK];
int qv;

int cntkdt;
int root;
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
int sum[MAXN];
int minv[MAXN][MAXK];
int maxv[MAXN][MAXK];
int addtag[MAXN];

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
int init(){
    cntkdt++;
    for(int d=0;d<k;d++){
        pos[cntkdt][d]=qx[d];
        minv[cntkdt][d]=maxv[cntkdt][d]=qx[d];
    }
    val[cntkdt]=qv;
    ls[cntkdt]=rs[cntkdt]=0;
    sz[cntkdt]=1;
    sum[cntkdt]=qv;
    addtag[cntkdt]=0;
    return cntkdt;
}

int compare(int i,int j,int dimension){
    int v1=pos[i][dimension];
    int v2=pos[j][dimension];
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
    sum[i]=sum[ls[i]]+sum[rs[i]]+val[i];
    for(int d=0;d<k;d++){
        minv[i][d]=min(pos[i][d],min(minv[ls[i]][d],minv[rs[i]][d]));
        maxv[i][d]=max(pos[i][d],max(maxv[ls[i]][d],maxv[rs[i]][d]));
    }
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
    ls[rt]=build(l,mid-1,(dimension+1)%k);
    rs[rt]=build(mid+1,r,(dimension+1)%k);
    maintain(rt);
    return rt;
}

void lazy(int i,int v){
    if(i!=0){
        val[i]+=v;
        sum[i]+=v*sz[i];
        addtag[i]+=v;
    }
}

void down(int i){
    if(addtag[i]!=0){
        lazy(ls[i],addtag[i]);
        lazy(rs[i],addtag[i]);
        addtag[i]=0;
    }
}

// 收集整个不平衡子树  准备重构
void dfs(int u){
    if(u){
        down(u);
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
    down(u);
    if(compare(insertNode,u,dimension)<=0){
        ls[u]=add(insertNode,ls[u],u,1,(dimension+1)%k);
    }
    else{
        rs[u]=add(insertNode,rs[u],u,2,(dimension+1)%k);
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
void addNode(){
    // 可能会导致不平衡 所以提前设置一下
    top=topFather=topSide=topDimension=0;
    // 初始化一个kd树节点
    int insertnode=init();
    root=add(insertnode,root,0,0,0);
    rebuild();
}

// 判断操作区域是否和节点i的区域无交集
bool outside(int i){
    for(int d=0;d<k;d++){
        if(maxv[i][d]<qx[d]||minv[i][d]>qy[d]){
            return true;
        }
    }
    return false;
}

// 判断操作区域是否包含包住节点i的区域
bool covered(int i){
    for(int d=0;d<k;d++){
        if(qx[d]>minv[i][d]||qy[d]<maxv[i][d]){
            return false;
        }
    }
    return true;
}

// 判断操作区域是否包含节点i这个单点
bool pointIn(int i){
    for(int d=0;d<k;d++){
        if(qx[d]>pos[i][d]||qy[d]<pos[i][d]){
            return false;
        }
    }
    return true;
}

// 来到了i号点，如果有给出范围覆盖的区间则加上qv  
void addValue(int i){
    if(i==0){
        return ;
    }
    if(outside(i)){
        return ;
    }
    if(covered(i)){
        lazy(i,qv);
        return ;
    }
    if(pointIn(i)){
        val[i]+=qv;
    }
    down(i);
    addValue(ls[i]);
    addValue(rs[i]);
    maintain(i);
}

// 来到了i号点，如果有给出范围覆盖的区间 查询答案 
int querySum(int i){
    if(i==0){
        return 0;
    }
    if(outside(i)){
        return 0;
    }
    if(covered(i)){
        return sum[i];
    }
    int ans=0;
    if(pointIn(i)){
        ans+=val[i];
    }
    down(i);
    ans+=querySum(ls[i]);
    ans+=querySum(rs[i]);
    return ans;
}

signed main()
{
    cin>>k>>m;
    for(int d=0;d<k;d++){
        minv[0][d]=INF;
        maxv[0][d]=-INF;
    }
    int lastans=0;
    for(int i=1,op;i<=m;i++){
        cin>>op;
        if(op==1){
            for(int d=0;d<k;d++){
                cin>>qx[d];
                qx[d]^=lastans;
            }
            cin>>qv;
            qv^=lastans;
            addNode();
        }
        else{
            for(int d=0;d<k;d++){
                cin>>qx[d];
                qx[d]^=lastans;
            }
            for(int d=0;d<k;d++){
                cin>>qy[d];
                qy[d]^=lastans;
            }
            if(op==2){
                cin>>qv;
                qv^=lastans;
                addValue(root);
            }
            else{
                lastans=querySum(root);
                cout<<lastans<<endl;
            }
        }
    }
    return 0;
}