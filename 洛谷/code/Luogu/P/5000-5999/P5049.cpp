#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n,m;

struct Edge{
    int u,v;
};
Edge arr[MAXN<<1];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int dfncnt;
int dfn[MAXN];
int from[MAXN];
bool cycle[MAXN];

int ans[MAXN];
int cnta;
bool turn;
bool vis[MAXN];

bool cmp(Edge &a,Edge &b){
    if(a.u!=b.u){
        return a.u<b.u;
    }
    return a.v>b.v;
}

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs(int u) {
    dfn[u] = ++dfncnt;
    for (int e = head[u]; e > 0; e = nxt[e]) {
        int v = to[e];
        if (dfn[v] == 0) {
            from[v] = u;
            dfs(v);
        } else if (dfn[u] < dfn[v]) {
            cycle[u] = true;
            for (int i = v; i != u; i = from[i]) {
                cycle[i] = true;
            }
        }
    }
}

void path(int u, int back) {
    vis[u] = true;
    ans[++cnta] = u;
    if (!cycle[u] || turn) {
        for (int e = head[u]; e > 0; e = nxt[e]) {
            int v = to[e];
            if (!vis[v]) {
                path(v, n + 1);
            }
        }
        return;
    }
    
    int end = 0;
    for (int e = head[u]; e > 0; e = nxt[e]) {
        int v = to[e];
        if (!vis[v]) {
            end = v;
        }
    }
    turn = cycle[end] && end > back;
    if (turn) {
        for (int e = head[u]; e > 0; e = nxt[e]) {
            int v = to[e];
            if (!vis[v] && v != end) {
                path(v, n + 1);
            }
        }
        return;
    }

    for (int e = head[u]; e > 0; e = nxt[e]) {
        int v = to[e];
        if (!vis[v]) {
            if (!cycle[v]) {
                path(v, n + 1);
            } else {
                int next = back;
                for (int ne = nxt[e]; ne > 0; ne = nxt[ne]) {
                    int nv = to[ne];
                    if (!vis[nv]) {
                        next = nv;
                        break;
                    }
                }
                path(v, next);
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        arr[i]={u,v};
        arr[i+m]={v,u};
    }
    sort(arr+1,arr+2*m+1,cmp);
    for(int i=1;i<=2*m;i++){
        addedge(arr[i].u,arr[i].v);
    }
    dfs(1);
    path(1,n+1);
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<' ';
    }
    return 0;
}