#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXK = 1e6+5;
const int INF = 1e9+5;

int n,k;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

bool vis[MAXN];
int sz[MAXN];

int dist[MAXN];
int edges[MAXN];
int cntc;

int alldis[MAXN];
int cnta;

int dp[MAXK];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
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
            if(v!=fa&&!vis[v]&&sz[v]>half){
                fa=u;
                u=v;
                find=false;
                break;
            }
        }
    }
    return u;
}

void dfs(int u,int fa,int dis,int edge){
    if(dis>k){
        return;
    }
    dist[++cntc]=dis;
    edges[cntc]=edge;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=fa&&!vis[v]){
            dfs(v,u,dis+w,edge+1);
        }
    }
}

int calc(int u){
    int ans=INF;
    cnta=0;
    dp[0]=0;
    for(int ei=head[u];ei;ei=nxt[ei]){
        int v=to[ei];
        int w=weight[ei];
        if(!vis[v]){
            cntc=0;
            dfs(v,u,w,1);
            for(int i=1;i<=cntc;i++){
                ans=min(ans,dp[k-dist[i]]+edges[i]);
            }
            for(int i=1;i<=cntc;i++){
                alldis[++cnta]=dist[i];
                dp[dist[i]]=min(dp[dist[i]],edges[i]);
            }
        }
    }
    for(int i=1;i<=cnta;i++){
        dp[alldis[i]]=INF;
    }
    return ans;
}

int compute(int u){
    vis[u]=true;
    int ans=calc(u);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]){
            ans=min(ans,compute(getcentroid(v,u)));
        }
    }
    return ans;
}

int main()
{
    n=read(),k=read();
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        // u++,v++;
        addedge(u,v,w);
        addedge(v,u,w);
    }
    for(int i=0;i<=k;i++){
        dp[i]=INF;
    }
    int ans=compute(getcentroid(1,0));
    if(ans==INF){
        ans=-1;
    }
    cout<<ans<<endl;
    return 0;
}