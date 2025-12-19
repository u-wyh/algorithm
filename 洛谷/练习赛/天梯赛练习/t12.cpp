#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;
const int MAXM = 1e4+5;
const int INF = 1e9;

int n,m,st,en;

int val[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];

int dis[MAXN];
bool vis[MAXN];

struct cmp{
    bool operator()(pair<int,int>a,pair<int,int>b){
        return a.second>b.second;
    }
};
priority_queue<pair<int,int>,vector<pair<int,int>>,cmp>heap;

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dijkstra(int limit){
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
        vis[u]=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(val[v]>limit&&v!=en){
                continue;
            }
            if(w+dis[u]<dis[v]){
                dis[v]=dis[u]+w;
                heap.push({v,dis[v]});
            }
        }
    }
}

int main()
{
    cin>>n>>m>>st>>en;
    int l=0,r=0;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        r=max(r,val[i]);
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dijkstra(r);
    int ans=dis[en];
    if(ans==INF){
        cout<<"Impossible";
        return 0;
    }
    int res=INF;
    while(l<=r){
        int mid=(l+r)/2;
        dijkstra(mid);
        if(dis[en]==ans){
            res=min(mid,res);
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    cout<<ans<<' '<<res<<endl;
    return 0;
}