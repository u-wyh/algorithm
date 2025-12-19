// https://www.luogu.com.cn/problem/P3639
//这道题是真的很厉害  这个想法很独特   如果对最小生成树  并查集不是非常了解 根本做不出来
//这道题说明 如果读题不清晰  思路不清楚的时候  就不要走一步看一步
//如果有把握 那么可以先写写   要不然思路可能就是错的
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 3e5+5;
const int MAXK = 25;

int n,m,k;
int val[MAXN];//每个节点的人数

//使用原图上一定会存在于最小生成树上的边形成的联通块
int blockcnt;
int block[MAXN];//每个节点属于哪个联通块
long long sz[MAXN];//每个联通块大小

//最初的并查集  在联通块缩点之后  也用于联通块的并查集
int fa[MAXN];

struct node{
    int u,v,w;
};
node edge[MAXM];//原图上的边
node e[MAXK];//新加的边

//原图中一定可以出现的边  编号集合
int init[MAXM];
int initcnt;
//原图中候补边  编号集合
int cand[MAXK];
int candcnt;

//联通块建图  用于设置新加边的权值
//其实只有这个联通块建的图才有效  因为只有这个上面才会有新加的边   才会对答案有影响
int head[MAXK];
int nxt[MAXK<<1];
int to[MAXK<<1];
int weight[MAXK<<1];
int kind[MAXK<<1];//用于判断是新加的边（1）还是候补的边（0）
int cnt=1;

//在联通块全部形成一个大联通块后  做dfs准备更新新加边的边权
int id[MAXN];//在此时的连线情况下  这个节点到父亲的边的编号
int dep[MAXN];
int parent[MAXN];

long long all[MAXN];//子树的大小
long long ans=0;
long long res=0;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

bool cmp(node u,node v){
    return u.w<v.w;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

inline void add(int u,int v,int w,int p){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    kind[cnt]=p;
    head[u]=cnt++;
}

//每次枚举新加边的边集时   清空不必要的信息
void prepare(){
    for(int i=1;i<=blockcnt;i++){
        fa[i]=i;
        head[i]=0;
    }
    cnt=1;
}

//此时所有必要的线已经连接  做出dfs
void dfs(int u,int fa){
    parent[u]=fa;
    dep[u]=dep[fa]+1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        id[v]=i;
        dfs(v,u);
    }
}

//联通块编号u v之间的所有还没有更新权值的新加边  权值更新为w
//因为节点很少  所以直接就是暴力
void update(int u,int v,int w){
    if(dep[u]<dep[v]){
        swap(u,v);
    }
    while(dep[u]>dep[v]){
        if(weight[id[u]]==0){
            weight[id[u]]=w;
            // weight[((id[u]-1)^1)+1]=w;//反边对答案没有什么影响  可以不用更新
        }
        u=parent[u];
    }
    if(u==v){
        return ;
    }
    while(parent[u]!=parent[v]){
        if(weight[id[u]]==0){
            weight[id[u]]=w;
        }
        u=parent[u];
        if(weight[id[v]]==0){
            weight[id[v]]=w;
        }
        v=parent[v];
    }
    if(weight[id[u]]==0){
        weight[id[u]]=w;
    }
    if(weight[id[v]]==0){
        weight[id[v]]=w;
    }
}

void dfs1(int u,int fa){
    all[u]=sz[u];
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs1(v,u);
        all[u]+=all[v];
        ans+=all[v]*kind[i]*weight[i];//如果这条边是新加的   那么记录对答案的贡献
    }
}

int main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        edge[i].u=read();
        edge[i].v=read();
        edge[i].w=read();
    }
    for(int i=1;i<=k;i++){
        e[i].u=read(),e[i].v=read();
    }
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    sort(edge+1,edge+m+1,cmp);
    //将k条边全部加进去
    for(int i=1;i<=k;i++){
        int u=e[i].u,v=e[i].v;
        int fu=find(u),fv=find(v);
        if(fu!=fv){
            fa[fu]=fv;
        }
    }
    //将原图中一定会存在的边加进去
    for(int i=1;i<=m;i++){
        int u=edge[i].u,v=edge[i].v;
        int fu=find(u),fv=find(v);
        if(fu!=fv){
            fa[fu]=fv;
            init[++initcnt]=i;
        }
    }

    //重置并查集
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }

    //将原图中一定会存在的边再次加进去
    for(int i=1;i<=initcnt;i++){
        int id=init[i];
        int u=edge[id].u,v=edge[id].v;
        int fu=find(u),fv=find(v);
        fa[fu]=fv;
    }
    //联通块缩点
    for(int i=1;i<=n;i++){
        int f=find(i);
        if(block[f]==0){
            block[f]=++blockcnt;
        }
        block[i]=block[f];
        sz[block[i]]+=val[i];
    }
    //处理出待选边
    for(int i=1;i<=m;i++){
        int u=edge[i].u,v=edge[i].v;
        int fu=find(u),fv=find(v);
        if(fu!=fv){
            cand[++candcnt]=i;
            fa[fu]=fv;
        }
    }

    //枚举加入的边集
    for(int st=1;st<(1<<k);st++){
        prepare();
        for(int i=1;i<=k;i++){
            if(st&(1<<(i-1))){
                int u=e[i].u,v=e[i].v;
                int fu=find(block[u]),fv=find(block[v]);
                if(fu!=fv){
                    add(block[u],block[v],0,1);
                    add(block[v],block[u],0,1);
                    fa[fu]=fv;
                }
            }
        }
        for(int i=1;i<=candcnt;i++){
            int id=cand[i];
            int u=edge[id].u,v=edge[id].v,w=edge[id].w;
            int fu=find(block[u]),fv=find(block[v]);
            if(fu!=fv){
                add(block[u],block[v],w,0);
                add(block[v],block[u],w,0);
                fa[fu]=fv;
            }
        }
        dfs(block[1],0);
        for(int i=1;i<=candcnt;i++){
            int id=cand[i];
            int u=edge[id].u,v=edge[id].v;
            int fu=find(block[u]),fv=find(block[v]);
            if(fu==fv){
                update(block[u],block[v],edge[id].w);
            }
        }
        ans=0;
        dfs1(block[1],0);
        res=max(ans,res);
    }

    cout<<res<<endl;
    return 0;
}