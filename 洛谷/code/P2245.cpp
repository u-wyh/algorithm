#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXM = 3e5+5;
const int MAXH = 20;

int n,m,q,p;

struct Edge{
    int u,v,w;
};
Edge edge[MAXM];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

int cntq;
int val[MAXN];

int fa[MAXN];

int st[MAXN][MAXH];
int dep[MAXN];

bool cmp(Edge &a,Edge &b){
    return a.w<b.w;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void kruskalrebuild(){
    sort(edge+1,edge+m+1,cmp);

    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    cntq=n;
    for(int i=1;i<=m;i++){
        int u=find(edge[i].u);
        int v=find(edge[i].v);
        if(u!=v){
            ++cntq;
            addedge(cntq,u);
            addedge(cntq,v);
            fa[cntq]=cntq;
            fa[u]=cntq;
            fa[v]=cntq;

            val[cntq]=edge[i].w;
        }
    }
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v,u);
    }
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=p;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }

    for(int i=p;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>edge[i].u>>edge[i].v>>edge[i].w;
    }

    p=log2(n)+2;

    kruskalrebuild();
    for(int i=1;i<=cntq;i++){
        if(fa[i]==i){
            dfs(i,0);
        }
    }

    cin>>q;
    for(int i=1;i<=q;i++){
        int u,v;
        cin>>u>>v;
        if(find(u)!=find(v)){
            cout<<"impossible"<<endl;
            continue;
        }
        cout<<val[lca(u,v)]<<endl;
    }
    return 0;
}