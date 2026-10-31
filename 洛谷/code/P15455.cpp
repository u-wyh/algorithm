// https://www.luogu.com.cn/problem/P15455
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
const int MAXM = 6e5+5;

int n,m,q;

struct Edge{
    int u,v,w;
};
Edge edge[MAXM];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int sz[MAXN];

int headg[MAXM];
int nxtg[MAXM];
int tog[MAXM];
int cntg=1;

int cntn;
int key[MAXM];

long long ans[MAXM];

int fa[MAXM];
int siz[MAXM];

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
    }
}

bool cmp(Edge &a,Edge &b){
    return a.w<b.w;
}

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

inline void addedgeg(int u,int v){
    nxtg[cntg]=headg[u];
    tog[cntg]=v;
    headg[u]=cntg++;
}

void build(){
    sort(edge+1,edge+m+1,cmp);
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }

    // 建立最小生成树
    for(int i=1;i<=m;i++){
        int u=edge[i].u;
        int v=edge[i].v;
        if(find(u)!=find(v)){
            addedge(u,v);
            addedge(v,u);
            un(u,v);
        }
    }

    // 建立kruskal重构树
    cntn=n;
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        int u=edge[i].u;
        int v=edge[i].v;
        int fu=find(u);
        int fv=find(v);
        if(fu!=fv){
            int rt=++cntn;
            fa[rt]=rt;
            key[rt]=i;
            addedgeg(rt,fu);
            addedgeg(rt,fv);
            fa[fu]=rt;
            fa[fv]=rt;
        }
    }
}

void dfs1(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs1(v,u);
            sz[u]+=sz[v];
        }
    }
}

void dfs2(int u){
    siz[u]=(u<=n)?1:0;
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        dfs2(v);
        siz[u]+=siz[v];
    }

    if(headg[u]){
        int ls=tog[headg[u]];
        int rs=tog[nxtg[headg[u]]];
        int e=key[u];

        int szls=sz[edge[e].v];
        int szrs=sz[edge[e].u];
        if(szls<szrs){
            szrs=n-szls;
        }
        else{
            szls=n-szrs;
        }

        ans[rs]+=1ll*szls*siz[ls];
        ans[ls]+=1ll*szrs*siz[rs];
    }
}

void dfs3(int u){
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        ans[v]+=ans[u];
        dfs3(v);
    }
}

void compute(){
    dfs1(1,0);
    dfs2(cntn);
    dfs3(cntn);
}

int main()
{
    cin>>n>>m>>q;

    for(int i=1;i<=m;i++){
        cin>>edge[i].u>>edge[i].v>>edge[i].w;
    }

    build();

    compute();

    for(int i=1;i<=q;i++){
        int u;
        cin>>u;
        cout<<ans[u]<<endl;
    }
    return 0;
}