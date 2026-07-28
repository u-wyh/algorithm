#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXH = 18;

int n,m,q,p;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=2;

int ex[MAXN];
int ey[MAXN];
int ev[MAXN];

int dfncnt;
int dfn[MAXN];
int low[MAXN];
int sta[MAXN];
int top;

int ebccCnt;
int belong[MAXN];

int headq[MAXN];
int nxtq[MAXN<<1];
int toq[MAXN<<1];
int idq[MAXN<<1];
int cntq=1;

int up[MAXN];
int dn[MAXN];

int dep[MAXN];
int st[MAXN][MAXH];

bool vis[MAXN];

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void tarjan(int u,int preedge){
    dfn[u]=low[u]=++dfncnt;
    sta[++top]=u;
    for(int i=head[u];i;i=nxt[i]){
        if((i^1)==preedge){
            continue;
        }

        int v=to[i];
        if(dfn[v]==0){
            tarjan(v,i);
            low[u]=min(low[u],low[v]);
        }
        else{
            low[u]=min(low[u],dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        ebccCnt++;
        int pop;
        do {
            pop = sta[top--];
            belong[pop]=ebccCnt;
        } while (pop != u);
    }
}

inline void addedgeq(int u,int v,int id){
    nxtq[cntq]=headq[u];
    toq[cntq]=v;
    idq[cntq]=id;
    headq[u]=cntq++;
}

void condense(){
    for(int i=1;i<=m;i++){
        int x=ex[i];
        int y=ey[i];
        x=belong[x];
        y=belong[y];

        if(x!=y){
            addedgeq(x,y,i);
            addedgeq(y,x,i+m);
        }
        else{
            ev[i]=2;
        }
    }
}

void dfs(int u,int fa){
    vis[u]=true;
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=headq[u];i;i=nxtq[i]){
        int v=toq[i];
        if(v!=fa){
            dfs(v,u);
        }
    }
}

int lca(int x,int y){
    if(dep[x]<dep[y]){
        swap(x,y);
    }
    for(int i=p;i>=0;i--){
        if(dep[st[x][i]]>=dep[y]){
            x=st[x][i];
        }
    }
    if(x==y){
        return x;
    }

    for(int i=p;i>=0;i--){
        if(st[x][i]!=st[y][i]){
            x=st[x][i];
            y=st[y][i];
        }
    }
    return st[x][0];
}

void calc(int x,int y){
    x=belong[x];
    y=belong[y];
    if(x==y){
        return ;
    }

    int fa=lca(x,y);
    up[x]++;
    up[fa]--;
    dn[y]++;
    dn[fa]--;
}

void dfs1(int u,int fa){
    vis[u]=true;
    for(int i=headq[u];i;i=nxtq[i]){
        int v=toq[i];
        int id=idq[i];
        if(v!=fa){
            dfs1(v,u);

            up[u]+=up[v];
            dn[u]+=dn[v];

            if(up[v]){
                if(id>m){
                    ev[id-m]=0;
                }
                else{
                    ev[id]=1;
                }
            }
            else if(dn[v]){
                if(id>m){
                    ev[id-m]=1;
                }
                else{
                    ev[id]=0;
                }
            }
            else{
                int eid=(id>m)?id-m:id;
                ev[eid]=2;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n>>m;
    p=log2(n)+1;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
        ex[i]=u,ey[i]=v;
    }

    for (int i = 1; i <= n; i++) {
        if (dfn[i] == 0) {
            tarjan(i, 0);
        }
    }
    condense();
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i, 0);
        }
    }

    cin>>q;
    for(int i=1;i<=q;i++){
        int x,y;
        cin>>x>>y;
        calc(x,y);
    }

    for(int i=1;i<=n;i++){
        vis[i]=false;
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs1(i, 0);
        }
    }

    for(int i=1;i<=m;i++){
        if(ev[i]==0){
            cout<<'R';
        }
        else if(ev[i]==1){
            cout<<'L';
        }
        else{
            cout<<'B';
        }
    }
    return 0;
}