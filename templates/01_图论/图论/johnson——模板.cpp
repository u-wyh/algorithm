// https://www.luogu.com.cn/problem/P5905
//johnson算法 就是预设一个势能值（通过spfa）  然后n轮dijkstra
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e3+5;
const int MAXM = 1e4+5;
const int INF = 1e15;

int n,m;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;

int h[MAXN];

int dis[MAXN];
long long ans;

queue<int>q;
int updatecnt[MAXN];
bool in[MAXN];

bool vis[MAXN];
struct cmp{
    bool operator()(pair<int,int>a,pair<int,int>b){
        return a.first>b.first;
    }
};
priority_queue<pair<int,int>,vector<pair<int,int>>,cmp>heap;

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void spfa(){
    for(int i=1;i<=n;i++){
        h[i]=1e9;
    }
    h[n+1]=0;
    q.push(n+1);
    in[n+1]=true;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        in[u]=false;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(h[u]+w<h[v]){
                h[v]=h[u]+w;
                if(!in[v]){
                    if(++updatecnt[v]>n){
                        cout<<-1<<endl;
                        exit(0);
                    }
                    q.push(v);
                    in[v]=true;
                }
            }
        }
    }
}

void dijkstra(int s){
    for(int i=1;i<=n;i++){
        dis[i]=INF;
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
        vis[u]=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(!vis[v]&&dis[u]+w<dis[v]){
                dis[v]=w+dis[u];
                heap.push({dis[v],v});
            }
        }
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
    }

    for(int i=1;i<=n;i++){
        addedge(n+1,i,0);
    }
    spfa();

    for(int u=1;u<=n;u++){
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            weight[i]+=h[u]-h[v];
        }
    }

    for(int i=1;i<=n;i++){
        dijkstra(i);
        ans=0;
        for(int j=1;j<=n;j++){
            if(dis[j]==INF){
                dis[j]=1e9;
                ans+=j*dis[j];
            }
            else{
                ans+=j*(dis[j]+h[j]-h[i]);
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}