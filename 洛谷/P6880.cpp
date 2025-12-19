#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 205;
const int MAXM = 5e4+5;

int n,m;
int ans=INT_MAX;

int cnt=1;
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];
int val[MAXM];

int tot=1;
int head1[MAXN];
int nxt1[MAXM];
int to1[MAXM];
int weight1[MAXM];

bool vis[MAXN];
int dis1[MAXN];
int dis2[MAXN];
int dis3[MAXN];
int dis4[MAXN];

struct compare{
    bool operator()(const pair<int,int>&a,const pair<int,int>&b){
        return a.second>b.second;
    }
};
priority_queue<pair<int,int>,vector<pair<int,int>>,compare>heap;

void addedge(int u,int v,int w,int k){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    val[cnt]=k;
    head[u]=cnt++;
}

void addedge(int u,int v,int w){
    nxt1[tot]=head1[u];
    to1[tot]=v;
    weight1[tot]=w;
    head1[u]=tot++;
}

void dijkstra(int st,int *head,int *nxt,int *to,int *weight,int *dis){
    for(int i=1;i<=n;i++){
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

void dfs(int u){
    if(vis[u]){
        return;
    }
    // cout<<' '<<u<<endl;
    vis[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        ans=min(ans,val[i]+min(dis1[n],dis1[v]+w+dis4[u])+min(dis3[1],dis3[v]+w+dis2[u]));
        dfs(v);
    }
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w,k;
        cin>>u>>v>>w>>k;
        addedge(u,v,w,k);
        addedge(v,u,w);
    }
    dijkstra(1,head,nxt,to,weight,dis1);
    dijkstra(n,head,nxt,to,weight,dis3);
    dijkstra(1,head1,nxt1,to1,weight1,dis2);
    dijkstra(n,head1,nxt1,to1,weight1,dis4);
    for(int i=1;i<=n;i++){
        cout<<dis1[i]<<' '<<dis2[i]<<' '<<dis3[i]<<' '<<dis4[i]<<endl;
    }
    cout<<endl;
    for(int i=1;i<=n;i++){
        vis[i]=false;
    }
    ans=min(ans,dis1[n]+dis3[1]);
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            dfs(i);
        }
    }
    if(ans>=INT_MAX){
        cout<<-1<<endl;
    }
    else{
        cout<<ans<<endl;
    }
    return 0;
}