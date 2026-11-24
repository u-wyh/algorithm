// 用途：Johnson 求稀疏图全源最短路。
// 时间：最坏 O(n²m + n(m+n)log n)。
// 空间：O(n+m)，每次 Dijkstra 复用距离数组。
// 例题：https://www.luogu.com.cn/problem/P5905
// 题意：稀疏有向图可含负边，求每对点最短距离。
// 思路：先求势能并重标边权，再从每个点运行 Dijkstra；负环则无解。
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
// h[u] 是超级源点到 u 的最短路，用作重标势能。

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
    // 超级源点连向所有点，先判负环并得到可使边权非负的势能。
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
    // 重标后边权非负；每个源点都重新初始化距离和已确定标记。
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
        // w'(u,v)=w(u,v)+h[u]-h[v]，最短路路径次序不变。
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            weight[i]+=h[u]-h[v];
        }
    }

    for(int i=1;i<=n;i++){
        dijkstra(i);
        ans=0;
        for(int j=1;j<=n;j++){
            // 有原路时还原 d=d'-h[i]+h[j]；无路按题目约定记 10^9。
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
