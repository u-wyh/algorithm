#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n;
int val[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cntg=1;

bool vis[MAXN];
int sz[MAXN];

int curL[MAXN];
int curR[MAXN];
int curtl,curtr;

int allL[MAXN];
int allR[MAXN];
int alltl,alltr;

int sum[MAXN];
int dis[MAXN];

void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;
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

void dfs(int u,int fa,int maxx,int minn){
    if((sum[u]-dis[u])>=maxx){
        curL[++curtl]=sum[u]-dis[u];
    }
    curR[++curtr]=minn;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=fa&&!vis[v]){
            sum[v]=sum[u]+val[v];
            dis[v]=dis[u]+w;
            dfs(v,u,max(maxx,sum[u]-dis[u]),min(minn,sum[u]-dis[v]));
        }
    }
}

int calc(int u){
    int ans=0;
    sum[u]=val[u];
    dis[u]=0;

    alltl=0,alltr=0;

    allL[++alltl]=sum[u];

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(!vis[v]){
            curtl=0,curtr=0;

            sum[v]=sum[u]+val[v];
            dis[v]=w;
            dfs(v,u,sum[u]-dis[u],sum[u]-dis[v]);

            ans+=curtl;

            for(int i=1;i<=curtl;i++){
                allL[++alltl]=curL[i];
            }
            for(int i=1;i<=curtr;i++){
                allR[++alltr]=curR[i];
            }

            sort(curL+1,curL+curtl+1);
            sort(curR+1,curR+curtr+1);

            for(int i=curtl,j=1;i>=1&&j<=curtr;i--){
                while((j<=curtr)&&(curL[i]+curR[j]<val[u])){
                    j++;
                }
                ans-=(curtr+1-j);
            }
        }
    }

    sort(allL+1,allL+alltl+1);
    sort(allR+1,allR+alltr+1);

    for(int i=alltl,j=1;i>=1&&j<=alltr;i--){
        while((j<=alltr)&&(allL[i]+allR[j]<val[u])){
            j++;
        }
        ans+=(alltr+1-j);
    }
    return ans;
}

int solve(int u){
    vis[u]=true;
    int ans=0;
    ans+=calc(u);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]){
            ans+=solve(getcentroid(v,u));
        }
    }
    return ans;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
    }

    int centroid=getcentroid(1,0);
    int ans=solve(centroid);
    cout<<ans<<endl;
    return 0;
}