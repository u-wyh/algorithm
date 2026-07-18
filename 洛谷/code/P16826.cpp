#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=5e5+5;
const int INF=1LL<<60;

int n,m;

int head[MAXN];
int nxt[MAXN*3];
int to[MAXN*3];
int weight[MAXN*3];
int cntg=1;

// 原树的父亲和DFS序
int pa[MAXN];
int dfn[MAXN];
int out[MAXN];
int dfncnt;

// dist表示DFS起点到各点的距离
// base表示各点在原树中的最远距离
int dist[MAXN];
int base[MAXN];

// 带权并查集
// dis表示节点到并查集父亲的距离
int fa[MAXN];
int dis[MAXN];

// 每个集合中到中心最远、次远的距离
// who表示取得最远距离的节点
int max1[MAXN];
int max2[MAXN];
int who[MAXN];

// 添加一条有向边
inline void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;
}

// 预处理原树父亲和DFS序
void dfs1(int u,int f){
    pa[u]=f;
    dfn[u]=++dfncnt;

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];

        if(v!=f){
            dist[v]=dist[u]+weight[i];
            dfs1(v,u);
        }
    }

    out[u]=dfncnt;
}

// 计算起点到所有节点的距离
void dfs2(int u,int f,int d){
    dist[u]=d;

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];

        if(v!=f){
            dfs2(v,u,d+weight[i]);
        }
    }
}

// 求原树直径端点，并计算每个点的原树最远距离
void prepare(){
    dfs1(1,0);

    int a=1;

    for(int i=2;i<=n;i++){
        if(dist[i]>dist[a]){
            a=i;
        }
    }

    dfs2(a,0,0);

    int b=1;

    for(int i=2;i<=n;i++){
        if(dist[i]>dist[b]){
            b=i;
        }
    }

    for(int i=1;i<=n;i++){
        base[i]=dist[i];
    }

    dfs2(b,0,0);

    for(int i=1;i<=n;i++){
        base[i]=max(base[i],dist[i]);

        fa[i]=i;
        dis[i]=0;

        max1[i]=0;
        max2[i]=-INF;
        who[i]=i;
    }
}

// 查找集合中心，并更新节点到中心的距离
int find(int x){
    if(x!=fa[x]){
        int f=fa[x];

        fa[x]=find(f);
        dis[x]+=dis[f];
    }

    return fa[x];
}

// 将x集合的信息合并到rt
// d表示x到rt的距离
void mergeinfo(int rt,int x,int d){
    int a1=max1[rt];
    int a2=max2[rt];

    int b1=max1[x]+d;
    int b2=max2[x]+d;

    if(b1>a1){
        max1[rt]=b1;
        max2[rt]=max(a1,b2);
        who[rt]=who[x];
    }
    else if(b1==a1){
        max2[rt]=a1;
    }
    else{
        max2[rt]=max(a2,b1);
    }
}

// 将u所在的核心分支全部压到rt
void absorb(int u,int f,int rt,int d){
    mergeinfo(rt,u,d);

    fa[u]=rt;
    dis[u]=d;

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];

        if(v!=f){
            absorb(v,u,rt,d+weight[i]);
        }
    }

    // u已经不再属于核心树
    head[u]=0;
}

// 判断x是否位于v经过son到达的方向
bool inbranch(int x,int v,int son){
    // son是v的儿子
    if(pa[son]==v){
        return dfn[son]<=dfn[x]&&dfn[x]<=out[son];
    }

    // son是v的父亲
    return !(dfn[v]<=dfn[x]&&dfn[x]<=out[v]);
}

// 处理一次道路修复
void modify(int u,int v){
    // v已经是叶子，灾害范围内没有道路
    if(find(v)!=v){
        return;
    }

    // u可能已经被压入某个核心点
    int rt=find(u);

    int keep=0;
    int keepw=0;

    for(int i=head[v];i;i=nxt[i]){
        int x=to[i];

        // 保留v通往u所在核心点的方向
        if(rt!=v&&inbranch(rt,v,x)){
            keep=x;
            keepw=weight[i];
        }
        else{
            absorb(x,v,v,weight[i]);
        }
    }

    // 清空v原来的所有核心边
    head[v]=0;

    // 只重新加入需要保留的方向
    if(keep){
        addedge(v,keep,keepw);
    }
}

// 查询x到其他城市的最大距离
int query(int x){
    int rt=find(x);
    int inside;

    // x本身是集合中最远点时，使用次远点
    if(who[rt]==x){
        inside=dis[x]+max2[rt];
    }
    else{
        inside=dis[x]+max1[rt];
    }

    return max(base[x],inside);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;

    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;

        addedge(u,v,w);
        addedge(v,u,w);
    }

    prepare();

    cin>>m;

    for(int i=1;i<=m;i++){
        int op,x,y;
        cin>>op>>x;

        if(op==1){
            cin>>y;
            modify(x,y);
        }
        else{
            cout<<query(x)<<'\n';
        }
    }

    return 0;
}