#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;
const int INF = 1e18;

int n,m,q;

int val[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];

int tot=1;
int head1[MAXN];
int nxt1[MAXM];
int to1[MAXM];
int weight1[MAXM];

int dis1[MAXN];
int dis2[MAXN];
bool vis[MAXN];

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void addEdge(int u,int v,int w){
    nxt1[tot]=head1[u];
    to1[tot]=v;
    weight1[tot]=w;
    head1[u]=tot++;
}

struct cmp{
    bool operator()(pair<int,int>a,pair<int,int>b){
        return a.second>b.second;
    }
};
priority_queue<pair<int,int>,vector<pair<int,int>>,cmp>heap;

void dijkstra(int st,int *dis,int *head,int *to,int *weight,int *nxt){
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
            if(w+dis[u]<dis[v]){
                dis[v]=dis[u]+w;
                heap.push({v,dis[v]});
            }
        }
    }
}

priority_queue<int,vector<int>,greater<int>>minheap;
map<int,int>ok;

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m>>q;
    for(int i=1;i<=m;i++){
        int u,v,c,d;
        cin>>u>>v>>c>>d;
        addedge(u,v,c);
        addEdge(v,u,d);
    }
    dijkstra(1,dis1,head,to,weight,nxt);
    dijkstra(n,dis2,head1,to1,weight1,nxt1);
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    for(int i=1;i<=n;i++){
        if(dis1[i]==INF||dis2[i]==INF){
            continue;
        }
        minheap.push(dis1[i]+(dis2[i]+val[i]-1)/val[i]);
        ok[dis1[i]+(dis2[i]+val[i]-1)/val[i]]++;
    }
    for(int i=1;i<=q;i++){
        int u,v;
        cin>>u>>v;
        if(dis1[u]==INF||dis2[u]==INF){
            cout<<minheap.top()<<endl;
            continue;
        }
        ok[dis1[u]+(dis2[u]+val[u]-1)/val[u]]--;
        val[u]=v;
        ok[dis1[u]+(dis2[u]+val[u]-1)/val[u]]++;
        minheap.push(dis1[u]+(dis2[u]+val[u]-1)/val[u]);
        while(!ok[minheap.top()]){
            minheap.pop();
        }
        cout<<minheap.top()<<endl;

    }
    return 0;
}