#include<bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 2005;
const int MAXM = 2005;
const int INF = 4e18;

int T;
int n,m,q;

int eu[MAXM];
int ev[MAXM];
int ew[MAXM];

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];
int cntg;

int dis[MAXN][MAXN];
bool vis[MAXN];

priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> heapq;

inline void addedge(int u,int v,int w){
    nxt[++cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg;
}

// 从s出发跑最短路
void dijkstra(int s){
    for(int i=1;i<=n;i++){
        dis[s][i]=INF;
        vis[i]=false;
    }

    while(!heapq.empty()){
        heapq.pop();
    }

    dis[s][s]=0;
    heapq.push({0,s});

    while(!heapq.empty()){
        int u=heapq.top().second;
        heapq.pop();

        if(vis[u]){
            continue;
        }

        vis[u]=true;

        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];

            if(dis[s][v]>dis[s][u]+w){
                dis[s][v]=dis[s][u]+w;
                heapq.push({dis[s][v],v});
            }
        }
    }
}

void solve(){
    cin>>n>>m>>q;

    cntg=0;

    for(int i=1;i<=n;i++){
        head[i]=0;
    }

    for(int i=1;i<=m;i++){
        cin>>eu[i]>>ev[i]>>ew[i];
        addedge(eu[i],ev[i],ew[i]);
    }

    // 原图全源最短路
    for(int i=1;i<=n;i++){
        dijkstra(i);
    }

    while(q--){
        int k,x;
        cin>>k>>x;

        int u=eu[k];
        int v=ev[k];

        long double ans=0;

        // 图的价值等于：
        // max(边 a->b 的反向最短路 dis(b,a) / 该边边权)
        for(int i=1;i<=m;i++){
            int a=eu[i];
            int b=ev[i];

            // 修改后从b到a的最短路
            // 要么完全不经过修改边
            // 要么经过一次 u->v
            int nd=min(
                dis[b][a],
                dis[b][u]+x+dis[v][a]
            );

            int w;

            if(i==k){
                w=x;
            }
            else{
                w=ew[i];
            }

            ans=max(ans,(long double)nd/w);
        }

        cout<<fixed<<setprecision(12)<<ans<<"\n";
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>T;

    while(T--){
        solve();
    }

    return 0;
}