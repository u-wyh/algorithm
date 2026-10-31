// https://www.luogu.com.cn/problem/P11852
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;
const int MAXM = 1e6+5;
const int INF = 1e9+5;

int n,m,q;

struct Edge{
    int u,v,w;
    bool used;
};
Edge edge[MAXM];

int ans[MAXN][MAXN];

int fa[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

bool cmp(Edge &a,Edge &b){
    return a.w<b.w;
}

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

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

int father[MAXN];
int dep[MAXN];
int val[MAXN];

void dfs1(int u,int f){
    dep[u]=dep[f]+1;
    father[u]=f;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
        }
    }
}

void dfs2(int s,int u,int f){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==f){
            continue;
        }
        int x=(dep[u]>dep[v])?u:v;
        ans[s][v]=max(ans[s][u],val[x]);
        dfs2(s,v,u);
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>edge[i].u>>edge[i].v>>edge[i].w;
    }
    sort(edge+1,edge+m+1,cmp);

    for(int i=1;i<=n;i++){
        fa[i]=i;
        val[i]=INF;
    }
    for(int i=1;i<=m;i++){
        int u=edge[i].u;
        int v=edge[i].v;

        if(find(u)!=find(v)){
            un(u,v);
            addedge(u,v);
            addedge(v,u);
            edge[i].used=true;
        }
    }

    dfs1(1,0);

    for(int i=1;i<=n;i++){
        fa[i]=i;
    }

    for(int i=1;i<=m;i++){
        if(edge[i].used){
            continue;
        }

        int u=find(edge[i].u);
        int v=find(edge[i].v);
        while(u!=v){
            if(dep[u]<dep[v]){
                swap(u,v);
            }
            val[u]=edge[i].w;
            un(u,father[u]);
            u=find(u);
        }
    }

    for(int i=1;i<=n;i++){
        ans[i][i]=0;
        dfs2(i,i,0);
    }

    cin>>q;
    for(int i=1;i<=q;i++){
        int a,b;
        cin>>a>>b;
        if(ans[a][b]==INF){
            cout<<-1<<endl;
        }
        else{
            cout<<ans[a][b]<<endl;
        }
    }
    return 0;
}