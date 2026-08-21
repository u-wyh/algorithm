#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e3+5;
const int INF = 1e18;

int n,m,q;

int eu[MAXN];
int ev[MAXN];
int ew[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int weight[MAXN];
int cntg=1;

int dis[MAXN][MAXN];
bool vis[MAXN];

struct compare{
    bool operator()(const pair<int,int>a,const pair<int,int>b){
        return a.second>b.second;
    }
};
priority_queue<pair<int,int>,vector<pair<int,int>>,compare>heap;

inline void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;
}

void init(){
    cntg=1;
    for(int i=1;i<=n;i++){
        head[i]=0;
    }
}

void dijkstra(int s){
    for(int i=1;i<=n;i++){
        vis[i]=false;
        dis[s][i]=INF;
    }

    dis[s][s]=0;
    heap.push({s,0});
    while(!heap.empty()){
        int u=heap.top().first;
        heap.pop();

        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            
            if(dis[s][v]>dis[s][u]+w){
                dis[s][v]=dis[s][u]+w;
                heap.push({v,dis[s][v]});
            }
        }
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;
    while(T--){
        cin>>n>>m>>q;
        init();

        for(int i=1;i<=m;i++){
            cin>>eu[i]>>ev[i]>>ew[i];
            addedge(eu[i],ev[i],ew[i]);
        }

        for(int i=1;i<=n;i++){
            dijkstra(i);
        }

        while(q--){
            int k,x,t;
            cin>>k>>x;
            t=ew[k];
            ew[k]=x;

            int u=eu[k];
            int v=ev[k];

            double ans=0;
            for(int i=1;i<=m;i++){
                int a=eu[i];
                int b=ev[i];
                int w=ew[i];
                int d=min(dis[b][a],dis[b][u]+x+dis[v][a]);
                ans=max(ans,1.0*d/w);
            }
            ew[k]=t;

            cout<<fixed<<setprecision(8)<<ans<<endl;
        }
    }
    return 0;
}