#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int headq[MAXN];
int nxtq[MAXN];
int toq[MAXN];
int idq[MAXN];
int cntq=1;

bool vis[MAXN];
int sz[MAXN];

struct node{
    int need,id;
};
node arr[MAXN];
int cnta;
int maxedge;

int ans[MAXN];

int nodecnt[MAXN];

void prepare(){
    cnt=1;
    cntq=1;
    for(int i=1;i<=n;i++){
        head[i]=0;
        headq[i]=0;
        vis[i]=false;
    }
    for(int i=1;i<=m;i++){
        ans[i]=false;
    }
}

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void addedgeq(int x,int k,int id){
    nxtq[cntq]=headq[x];
    toq[cntq]=k;
    idq[cntq]=id;
    headq[x]=cntq++;
}

void getsize(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa&&!vis[v]){
            getsize(v,u);
            sz[u]+=sz[v];
        }
    }
}

int getcentroid(int u,int fa){
    getsize(u,fa);
    int half=sz[u]>>1;
    bool find=false;
    while(!find){
        find=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v!=fa&&!vis[v]&&sz[v]>=half){
                fa=u;
                u=v;
                find=false;
                break;
            }
        }
    }
    return u;
}

void dfs(int u,int fa,int d){
    nodecnt[d]++;
    maxedge=max(maxedge,d);
    for(int i=headq[u];i;i=nxtq[i]){
        int v=toq[i];
        if(v>=d){
            arr[++cnta]={v-d,idq[i]};
        }
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa&&!vis[v]){
            dfs(v,u,d+1);
        }
    }
}

void calc(int u,int edge,int effect){
    cnta=0;
    maxedge=0;
    dfs(u,0,edge);
    for(int i=1;i<=cnta;i++){
        ans[arr[i].id]+=nodecnt[arr[i].need]*effect;
    }
    for(int v=0;v<=maxedge;v++){
        nodecnt[v]=0;
    }
}

void compute(int u){
    vis[u]=true;
    calc(u,0,1);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]){
            calc(v,1,-1);
            compute(getcentroid(v,u));
        }
    }
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        prepare();
        cin>>n>>m;
        for(int i=1;i<n;i++){
            int u,v;
            cin>>u>>v;
            addedge(u,v);
            addedge(v,u);
        }
        for(int i=1;i<=m;i++){
            int x,k;
            cin>>x>>k;
            addedgeq(x,k,i);
        }
        compute(getcentroid(1,0));
        for(int i=1;i<=m;i++){
            cout<<ans[i]<<endl;
        }
    }
    return 0;
}