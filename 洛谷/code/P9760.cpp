#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXM = 1e6+5;
const int MAXE = MAXN+MAXM;
const int MAXH = 20;

int n,m;
int a[MAXN];

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cntg=1;

int dfn[MAXN];
int low[MAXN];
int dfncnt;
int out[MAXN];

int dep[MAXN];
int st[MAXN][MAXH];

int head2[MAXN];
int nxt2[MAXE];
int to2[MAXE];
int cntg2=1;

bool win[MAXN];
int ans[MAXN];

int que[MAXN];

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

inline void addedge2(int u,int v){
    nxt2[cntg2]=head2[u];
    to2[cntg2]=v;
    head2[u]=cntg2++;
}

void tarjan(int u){
    dfn[u]=low[u]=++dfncnt;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];

        if(dfn[v]==0){
            dep[v]=dep[u]+1;
            st[v][0]=u;
            for(int i=1;i<MAXH;i++){
                st[v][i]=st[st[v][i-1]][i-1];
            }

            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else{
            low[u]=min(low[u],dfn[v]);
        }
    }
    out[u]=dfncnt;
}

bool inSubtree(int u, int v) {
    return dfn[u] <= dfn[v] && dfn[v] <= out[u];
}

// 删除 ban 后，x 所在连通块的编号
int getBlock(int ban, int x) {
    if (x == ban) {
        return -1;
    }

    if (!inSubtree(ban, x)) {
        return 0;
    }

    int cur = x;
    int up = dep[x] - dep[ban] - 1;

    for (int p = MAXH - 1; p >= 0; p--) {
        if (up & (1 << p)) {
            cur = st[cur][p];
        }
    }

    if (low[cur] >= dfn[ban]) {
        return cur;
    }

    return 0;
}

// Marin 从 v 走到 u 后，Luka 能否避开 u
bool canavoid(int v, int u) {
    if (a[v] == u || a[u] == u) {
        return false;
    }

    return getBlock(u, a[v]) == getBlock(u, a[u]);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }

    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }

    dep[1]=1;
    tarjan(1);

    for(int v=1;v<=n;v++){
        for(int i=head[v];i;i=nxt[i]){
            int u=to[i];
            if(canavoid(v,u)){
                addedge2(u,v);
            }
            else{
                win[v]=true;
            }
        }
    }

    for(int i=1;i<=n;i++){
        if(win[i]){
            addedge2(0,i);
        }
    }

    for(int i=1;i<=n;i++){
        ans[i]=-1;
    }

    int l=1,r=0;
    ans[0]=0;
    que[++r]=0;
    for(int i=1;i<=n;i++){
        if(a[i]==i){
            que[++r]=i;
            ans[i]=0;
        }
    }
    while(l<=r){
        int u=que[l++];
        for(int i=head2[u];i;i=nxt2[i]){
            int v=to2[i];

            if(ans[v]==-1){
                ans[v]=ans[u]+1;
                que[++r]=v;
            }
        }
    }

    for(int i=1;i<=n;i++){
        cout<<ans[i]<<' ';
    }
    return 0;
}