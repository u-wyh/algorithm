#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
int a[MAXN];
int b[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int ans[MAXN];

int fa[MAXN];
int sz[MAXN];
int edgecnt[MAXN];

int res;

int traceback[MAXN][2];
int opsize;

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

int find(int x){
    while(x!=fa[x]){
        x=fa[x];
    }
    return x;
}

void un(int fx,int fy){
    if(sz[fx]<sz[fy]){
        swap(fx,fy);
    }
    fa[fy]=fx;
    sz[fx]+=sz[fy];
    edgecnt[fx]+=edgecnt[fy]+1;
    traceback[++opsize][0]=fx;
    traceback[opsize][1]=fy;
}

void undo(){
    int fx=traceback[opsize][0];
    int fy=traceback[opsize][1];
    opsize--;
    fa[fy]=fy;
    sz[fx]-=sz[fy];
    edgecnt[fx]-=edgecnt[fy]+1;
}

void dfs(int u,int fa){
    int fx=find(a[u]);
    int fy=find(b[u]);
    bool added=false;
    bool unioned=false;
    if(fx==fy){
        if(edgecnt[fx]<sz[fx]){
            res++;
            added=true;
        }
        edgecnt[fx]++;
    }
    else{
        if(edgecnt[fx]<sz[fx]||edgecnt[fy]<sz[fy]){
            res++;
            added=true;
        }
        un(fx,fy);
        unioned=true;
    }
    ans[u]=res;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u);
        }
    }
    if(added){
        res--;
    }
    if(unioned){
        undo();
    }
    else{
        edgecnt[fx]--;
    }
}

void compute(){
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
    }

    dfs(1,0);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }

    compute();

    for(int i=2;i<=n;i++){
        cout<<ans[i]<<' ';
    }
    return 0;
}