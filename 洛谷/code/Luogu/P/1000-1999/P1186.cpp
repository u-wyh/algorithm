#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXM = 5e5+5;
const int INF = 1e9;

int n,m;
int dis[MAXN];
int dist[MAXN];
bool vis[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int weight[MAXM<<1];

struct compare{
    bool operator()(const pair<int,int>&a,const pair<int,int>&b){
        return a.second>b.second;
    }
};

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dijkstra(int *dis,int x,int y){
    priority_queue<pair<int,int>,vector<pair<int,int>>,compare>heap;
    for(int i=1;i<=n;i++){
        dis[i]=INF;
        vis[i]=false;
    }
    dis[n]=0;
    heap.push({n,0});
    while(!heap.empty()){
        int u=heap.top().first;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        if(u==1){
            break;
        }
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if((u==x&&v==y)||(u==y&&v==x)){
                continue;
            }
            if(dis[u]+w<dis[v]){
                dis[v]=dis[u]+w;
                heap.push({v,dis[v]});
            }
        }
    }
}


int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dijkstra(dis,0,0);
    int ans=0;
    for(int u=1;u<=n;u++){
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(dis[u]+w==dis[v]){
                dijkstra(dist,u,v);
                ans=max(ans,dist[1]);
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}