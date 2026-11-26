// https://www.luogu.com.cn/problem/P1186
// 题意：无向图有 N 个城市和 M 条带权双向路（两点间最多一条路），1 为终点 N 为起点。
// 题意：已知恰有一条路正在维修堵车（但图仍连通），玛丽卡会沿不堵车最短路前行。
// 题意：求最坏情况下（任意一条路堵车）她从 N 到 1 所需最短时间的最大值。
// 输入：第一行输入 N, M，接下来 M 行每行输入 A, B, V 表示边权为 V 的无向边。
// 输出：一行输出最坏情况下的最短通行时间（分钟）。
// 数据范围：1 <= N <= 1000，1 <= M <= N * (N - 1) / 2。
// 数据范围：1 <= A, B <= N，1 <= V <= 1000。
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