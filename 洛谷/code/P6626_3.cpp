#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int headq[MAXN];
int nxtq[MAXN];
int toq[MAXN];
int cntq=1;

int sz[MAXN];
bool vis[MAXN];
int ans[MAXN];

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void addedgeq(int u,int v){
    nxtq[cntq]=headq[u];
    toq[cntq]=v;
    headq[u]=cntq++;
}

void getsize(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]&&v!=fa){
            getsize(v,u);
            sz[u]+=sz[v];
        }
    }
}

int getcentroid(int u,int fa){
    getsize(u,fa);
    int half=sz[u]>>1;
    bool flag=false;
    while(!flag){
        flag=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v!=fa&&!vis[v]&&sz[v]>half){
                flag=false;
                fa=u;
                u=v;
                break;
            }
        }
    }
    return u;
}

struct node{
    int qid;
    int dis;
};
node nums[MAXN];
int cnt;

int discnt[MAXN];
int maxedge;

void dfs(int u,int fa,int edge){
    discnt[edge]++;
    maxedge=max(maxedge,edge);
    for(int i=headq[u];i;i=nxtq[i]){
        int v=toq[i];
        if(v>=edge){
            nums[++cnt]={i,v-edge};
        }
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa&&!vis[v]){
            dfs(v,u,edge+1);
        }
    }
}

void calc(int u,int edge,int op){
    maxedge=0;
    cnt=0;
    dfs(u,0,edge);
    for(int i=1;i<=cnt;i++){
        ans[nums[i].qid]+=op*discnt[nums[i].dis];
    }
    for(int i=0;i<=maxedge;i++){
        discnt[i]=0;
    }
}

void solve(int u){
    vis[u]=true;
    calc(u,0,1);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]){
            calc(v,1,-1);
            solve(getcentroid(v,u));
        }
    }
}

void init(){
    for(int i=1;i<=n;i++){
        head[i]=0;
        headq[i]=0;
        vis[i]=false;
    }
    cntq=1;
    cntg=1;
    for(int i=1;i<=m;i++){
        ans[i]=0;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        init();
        for(int i=1;i<n;i++){
            int u,v;
            cin>>u>>v;
            addedge(u,v);
            addedge(v,u);
        }
        for(int i=1;i<=m;i++){
            int u,v;
            cin>>u>>v;
            addedgeq(u,v);
        }

        int centroid=getcentroid(1,0);
        solve(centroid);

        for(int i=1;i<=m;i++){
            cout<<ans[i]<<endl;
        }
    }
    return 0;
}