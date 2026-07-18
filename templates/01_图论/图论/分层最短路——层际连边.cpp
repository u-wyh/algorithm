//P4822
//分层最短路
//这道题主要考察的是层际之间连边的方法
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 55;
const int MAXM = 100000;//这个要开大 因为有多层图之外 层际之间也要连边

int n,m,k;

int cnt=1;
int head[MAXN*55];
int nxt[MAXM<<1];
int to[MAXM<<1];
int weight[MAXM<<1];

bool vis[MAXN*55];
int dis[MAXN*55];

struct compare{
    bool operator()(const pair<int,int>&a,const pair<int,int>&b){
        return a.second>b.second;
    }
};
priority_queue<pair<int,int>,vector<pair<int,int>>,compare>heap;

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dijkstra(int st){
    for(int i=1;i<=n*(k+1);i++){
        dis[i]=INT_MAX;
        vis[i]=false;
    }
    dis[st]=0;
    heap.push({st,0});
    while(!heap.empty()){
        int u=heap.top().first;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=1;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                heap.push({v,dis[v]});
            }
        }
    }
}

int main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        for(int j=0;j<=k;j++){
            //建立k+1层图
            addedge(u+j*n,v+j*n,w);
            addedge(v+j*n,u+j*n,w);
        }
        for(int j=0;j<k;j++){
            //建立层际之间的路径
            addedge(u+j*n,v+n+j*n,w/2);
            addedge(v+j*n,u+n+j*n,w/2);
        }
    }
    dijkstra(1);
    int ans=INT_MAX;
    for(int i=0;i<=k;i++){
        //只要到达n号节点 不管是那一层  都可以
        ans=min(ans,dis[n+i*n]);
    }
    cout<<ans<<endl;
    return 0;
}
