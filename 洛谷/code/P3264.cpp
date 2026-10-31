// https://www.luogu.com.cn/problem/P3264
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;
const int MAXM = 6e3+5;
const int MAXS = 1<<10;
const int INF = 1e9;

int n,m,q;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];
int cntg=1;

int dp[MAXS][MAXN];
int cost[MAXS];
int f[MAXS];
int need[MAXS];

struct node{
    int u,d;
};
struct cmp{
    bool operator()(node &a,node &b){
        return a.d>b.d;
    }
};

inline void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;
}

void dijkstra(int s){
    priority_queue<node,vector<node>,cmp>heap;
    for(int i=1;i<=n;i++){
        if(dp[s][i]!=INF){
            heap.push({i,dp[s][i]});
        }
    }
    while(!heap.empty()){
        node tmp=heap.top();
        heap.pop();
        int u=tmp.u;
        if(tmp.d!=dp[s][u]){
            continue;
        }

        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(dp[s][v]>dp[s][u]+weight[i]){
                dp[s][v]=dp[s][u]+weight[i];
                heap.push({v,dp[s][v]});
            }
        }
    }
}

void steiner(){
    int limit=1<<q;
    for(int s=1;s<limit;s++){
        for(int t=(s-1)&s;t;t=(t-1)&s){
            int r=s^t;
            if(t>r){
                continue;
            }

            for(int u=1;u<=n;u++){
                dp[s][u]=min(dp[s][u],dp[t][u]+dp[r][u]);
            }
        }
        dijkstra(s);

        cost[s]=INF;
        for(int u=1;u<=n;u++){
            cost[s]=min(cost[s],dp[s][u]);
        }
    }
}

int main()
{
    cin>>n>>m>>q;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
    }

    for(int i=0;i<(1<<q);i++){
        for(int j=1;j<=n;j++){
            dp[i][j]=INF;
        }
    }
    for(int i=0;i<q;i++){
        int c,d;
        cin>>c>>d;
        dp[1<<i][d]=0;
        need[1<<(c-1)]|=(1<<i);
    }

    steiner();

    int limit=1<<q;
    for(int s=1;s<limit;s++){
        int lb=s&-s;
        // need[s]|=need[s^lb];
        need[s]=need[s^lb]|need[lb];
    }
    for(int i=0;i<limit;i++){
        f[i]=INF;
    }
    f[0]=0;

    for(int s=1;s<limit;s++){
        int lb=s&-s;

        for(int t=s;t;t=(t-1)&s){
            if(!(t&lb)) continue;

            int r=s^t;
            int k=need[t];

            if(f[r]==INF || cost[k]==INF) continue;

            f[s]=min(f[s],f[r]+cost[k]);
        }
    }

    cout<<f[limit-1]<<endl;
    return 0;
}