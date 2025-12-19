#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;
const int MAXK = 5;
const int MAXS = 32;
const long long INF = 1e18;

int n,k,m;
int key[MAXK];

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int weight[MAXM<<1];
int cnt=1;

long long dp[MAXS][MAXN];

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

struct node{
    int u;
    long long d;
};
struct compare{
    bool operator()(const node &a,const node &b){
        return a.d>b.d;
    }
};
priority_queue<node,vector<node>,compare>heap;
bool vis[MAXN];

int main()
{
    n=read(),k=read(),m=read();
    for(int i=0;i<k;i++){
        key[i]=read();
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    int status=(1<<k)-1;
    for(int i=0;i<=status;i++){
        for(int j=1;j<=n;j++){
            dp[i][j]=INF;
        }
    }
    for(int i=1;i<=k;i++){
        dp[1<<(i-1)][key[i-1]]=0;
    }
    for(int s=1;s<=status;s++){
        for(int sub=(s-1)&s;sub;sub=(sub-1)&s){
            int other=s-sub;
            for(int u=1;u<=n;u++){
                if(dp[sub][u]<INF&&dp[other][u]<INF){
                    dp[s][u]=min(dp[s][u],dp[sub][u]+dp[other][u]);
                }
            }
        }

        for(int i=1;i<=n;i++){
            vis[i]=false;
        }
        for(int u=1;u<=n;u++){
            if(dp[s][u]<INF){
                heap.push({u,dp[s][u]});
            }
        }
        while(!heap.empty()){
            int u=heap.top().u;
            heap.pop();
            if(vis[u]){
                continue;
            }
            vis[u]=true;
            for(int i=head[u];i;i=nxt[i]){
                int v=to[i];
                int w=weight[i];
                if(dp[s][v]>dp[s][u]+w){
                    dp[s][v]=dp[s][u]+w;
                    heap.push({v,dp[s][v]});
                }
            }
        }
    }


    long long ans=INF;
    for(int i=1;i<=n;i++){
        ans=min(ans,dp[status][i]);
    }
    cout<<ans<<endl;
    return 0;
}