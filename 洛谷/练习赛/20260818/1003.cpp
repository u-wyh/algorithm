#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;
const int MAXM = 3e5+5;

int n,m,s,t;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cntg=1;

int dis[MAXN];
bool vis[MAXN];
int neighbor[MAXN];

struct compare{
    bool operator()(const pair<int,int>&a,const pair<int,int>&b){
        return a.second>b.second;
    }
};
priority_queue<pair<int,int>,vector<pair<int,int>>,compare>heap;

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void init(){
    for(int i=1;i<=n;i++){
        head[i]=0;
    }
    cntg=1;
}

void dijkstra(){
    for(int i=1;i<=n;i++){
        dis[i]=MAXN;
        vis[i]=false;
        neighbor[i]=0;
    }

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
            if(dis[v]>dis[u]+1){
                heap.push({v,dis[v]});
            }
        }
    }
}

void compute(){
    for(int u=1;u<=n;u++){
        int d=dis[u];
        neighbor[u]=-1;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(dis[v]==d+1){
                neighbor[u]++;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;
    while(T--){
        cin>>n>>m>>s>>t;
        init();
        for(int i=1;i<=m;i++){
            int u,v;
            cin>>u>>v;
            addedge(u,v);
            addedge(v,u);
        }

        dijkstra();
        compute();
    }
    return 0;
}