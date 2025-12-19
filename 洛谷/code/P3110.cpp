#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e4+5;
const int INF = 1e9;

int n,m;
int a,b,c;

int dis1[MAXN];
int dis2[MAXN];
int dis[MAXN];
bool vis[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];

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

void dijkstra(int st,int *dis){
    for(int i=1;i<=n;i++){
        dis[i]=INF;
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
                dis[v]=w+dis[u];
                heap.push({v,dis[v]});
            }
        }
    }
}

int main()
{
    cin>>a>>b>>c>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v,1);
        addedge(v,u,1);
    }
    dijkstra(1,dis1);
    dijkstra(2,dis2);
    dijkstra(n,dis);
    int ans=INT_MAX;
    for(int i=1;i<=n;i++){
        ans=min(ans,a*dis1[i]+b*dis2[i]+c*dis[i]);
    }
    cout<<ans<<endl;
    return 0;
}