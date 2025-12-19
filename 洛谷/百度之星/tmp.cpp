#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXV = 505;
const int MAXE = 1e6+5;
const int INF = 1e9;

int n,m,s,t,k,l;
int mincost,maxflow;
int cnt1[MAXN];
int cnt2[MAXN];

queue<int>q;
bool in[MAXV];

int pot[MAXV];
int dis[MAXV];
int pre[MAXV];
bool vis[MAXV];

int head[MAXV];
int nxt[MAXE];
int to[MAXE];
int cap[MAXE];
int cost[MAXE];
int cnt=2;

int vec[MAXN];
int cnt3[MAXN];

struct cmp{
    bool operator()(pair<int,int>&a,pair<int,int>&b){
        return a.first>b.first;
    }
};
priority_queue<pair<int,int>,vector<pair<int,int>>,cmp>heap;

inline void addedge(int u,int v,int w,int c){
    nxt[cnt]=head[u];
    to[cnt]=v;
    cap[cnt]=w;
    cost[cnt]=c;
    head[u]=cnt++;

    nxt[cnt]=head[v];
    to[cnt]=u;
    cap[cnt]=0;
    cost[cnt]=-c;
    head[v]=cnt++;
}

void spfa(int s){
    for(int i=1;i<=t;i++){
        pot[i]=INF;
    }

    q.push(s);
    pot[s]=0;
    in[s]=1;

    while(!q.empty()){
        int u=q.front();
        q.pop();
        in[u]=false;

        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=cap[i];
            int c=cost[i];

            if(w>0&&pot[u]+c<pot[v]){
                pot[v]=pot[u]+c;
                if(!in[v]){
                    q.push(v);
                    in[v]=true;
                }
            }
        }
    }
}

bool dijkstra(){
    for(int i=1;i<=t;i++){
        dis[i]=INF;
        pre[i]=-1;
        vis[i]=false;
    }

    dis[s]=0;
    heap.push({0,s});
    while(!heap.empty()){
        int u=heap.top().second;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=1;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int residual=cap[i];
            int c_original=cost[i];
            if(residual<=0){
                continue;
            }
            int adjusted_cost=c_original+pot[u]-pot[v];
            if(dis[u]+adjusted_cost<dis[v]){
                dis[v]=dis[u]+adjusted_cost;
                pre[v]=i;
                heap.push({dis[v],v});
            }
        }
    }
    return dis[t]<INF;
}

void mincostmaxflow(){
    spfa(s);
    maxflow=0;
    mincost=0;
    while(dijkstra()){
        int flow=INF;
        for(int u=t;u!=s;u=to[pre[u]^1]){
            flow=min(flow,cap[pre[u]]);
        }
        maxflow+=flow;
        mincost+=flow*(dis[t]+pot[t]);
        for(int u=t;u!=s;u=to[pre[u]^1]){
            cap[pre[u]]-=flow;
            cap[pre[u]^1]+=flow;
        }
        for(int i=1;i<=t;i++){
            if(dis[i]<INF){
                pot[i]+=dis[i];
            }
        }
    }
}

int main()
{
    return 0;
}