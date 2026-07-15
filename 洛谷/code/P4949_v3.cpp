#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+10;

int n,m;

int u[MAXN];
int v[MAXN];
int w[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int dfncnt;
int dfn[MAXN];
int from[MAXN];
bool cycle[MAXN];
int arr[MAXN];
int cnta;

int cycleEdgeTo[MAXN];
int cycleId[MAXN];
int belong[MAXN];

int fa[MAXN];
int son[MAXN];
int sz[MAXN];
int top[MAXN];
int dep[MAXN];

int tree[MAXN<<1];

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs1(int u){
    dfn[u]=++dfncnt;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(dfn[v]==0){
            from[v]=u;
            cycleEdgeTo[(i+1)>>1]=v;
            dfs1(v);
        }
        else if(dfn[u]<dfn[v]) {
            cycleEdgeTo[(i+1)>>1]=u;
            cycle[u]=true;
            arr[++cnta]=u;
            for(int j=v;j!=u;j=from[j]){
                cycle[j]=true;
                arr[++cnta]=j;
            }
        }
    }
}

void dfs2(int u,int f,int h){
    sz[u]=1;
    dep[u]=dep[f]+1;
    fa[u]=f;
    belong[u]=h;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=f&&!cycle[v]){
            dfs2(v,u,h);
            sz[u]+=sz[v];
            if(sz[v]>sz[son[u]]){
                son[u]=v;
            }
        }
    }
}

void dfs3(int u,int t){
    top[u]=t;
    dfn[u]=++dfncnt;
    if(son[u]){
        dfs3(son[u],t);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa[u]&&v!=son[u]&&!cycle[v]){
            dfs3(v,v);
        }
    }
}

int lowbit(int x){
    return x&(-x);
}

void add(int x,int v){
    while(x<=dfncnt){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

int sum(int l,int r){
    if(l>r){
        return 0;
    }
    return query(r)-query(l-1);
}

int edgeToNode(int i){
    if (cycle[u[i]] && cycle[v[i]]) {
        return cycleId[cycleEdgeTo[i]];
    } else {
        return max(dfn[u[i]], dfn[v[i]]);
    }
}

void prepare(){
    dfs1(1);
    dfncnt=0;
    for(int i=1;i<=cnta;i++){
        dfs2(arr[i],0,arr[i]);
        dfs3(arr[i],arr[i]);
    }
    for(int i=1;i<=cnta;i++){
        cycleId[arr[i]]=++dfncnt;
    }
    for(int i=1;i<=n;i++){
        add(edgeToNode(i),w[i]);
    }
}

void setedge(int edge,int val){
    add(edgeToNode(edge),val-w[edge]);
    w[edge]=val;
}

int compute(int x,int y){
    int ans=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            swap(x,y);
        }
        ans+=sum(dfn[top[x]],dfn[x]);
        x=fa[top[x]];
    }
    ans+=sum(min(dfn[x],dfn[y])+1,max(dfn[x],dfn[y]));
    return ans;
}

int getdist(int x,int y){
    if(belong[x]==belong[y]){
        return compute(x,y);
    }
    else{
        int a = min(cycleId[belong[x]], cycleId[belong[y]]);
        int b = max(cycleId[belong[x]], cycleId[belong[y]]);
        int p1 = sum(a, b - 1);
        int p2 = sum(n + 1, dfncnt) - p1;
        return compute(x, belong[x]) + compute(y, belong[y]) + min(p1, p2);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>u[i]>>v[i]>>w[i];
        addedge(u[i],v[i]);
        addedge(v[i],u[i]);
    }

    prepare();

    for(int i=1;i<=m;i++){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1){
            setedge(x,y);
        }
        else{
            cout<<getdist(x,y)<<endl;
        }
    }
    return 0;
}