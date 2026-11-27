#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=2;

int dfncnt;
int dfn[MAXN];
int low[MAXN];
int sta[MAXN];
int top;

int ans[MAXN];
int deg[MAXN];
int tmp[MAXN];
int tag[MAXN];
int len;
int bcccnt;

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void init(){
    for(int i=1;i<=n;i++){
        head[i]=0;
        dfn[i]=low[i]=0;
        ans[i]=0;
        tag[i]=0;
    }
    cntg=2;
    dfncnt=0;
    top=0;
    bcccnt=0;
}

void getbcc(int edge){
    bcccnt++;
    len=0;

    while(true){
        int e=sta[top--];
        int u=to[e];
        int v=to[e^1];
        deg[u]++;
        deg[v]++;
        if(tag[u]!=bcccnt){
            tag[u]=bcccnt;
            tmp[++len]=u;
        }
        if(tag[v]!=bcccnt){
            tag[v]=bcccnt;
            tmp[++len]=v;
        }

        if(e==edge){
            break;
        }
    }

    for(int i=1;i<=len;i++){
        int u=tmp[i];
        ans[u]+=deg[u]/2;
        deg[u]=0;
    }
}

void tarjan(int u,int preedge){
    dfn[u]=low[u]=++dfncnt;
    for(int i=head[u];i;i=nxt[i]){
        if((i^1)==preedge){
            continue;
        }
        int v=to[i];
        if(!dfn[v]){
            sta[++top]=i;
            tarjan(v,i);
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u]){
                getbcc(i);
            }
        }
        else if(dfn[v]<dfn[u]){
            sta[++top]=i;
            low[u]=min(low[u],dfn[v]);
        }
    }
}

void solve(){
    cin>>n>>m;
    init();
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }

    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i,0);
        }
    }

    for(int i=1;i<=n;i++){
        cout<<ans[i]<<' ';
    }
    cout<<endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}