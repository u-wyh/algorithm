// https://www.luogu.com.cn/problem/P3905
// 题意：n 个城市间原有 m 条无向道路（无重边，第 t 条长 k），战后有 d 条道路被破坏。
// 给定起点 A 和终点 B，修复被破坏的道路需要花费等于其长度的代价，未破坏道路可直接通行。
// 求使 A 与 B 连通所需修复道路总长度的最小值。
// 数据范围：2 < n <= 100，n - 1 <= m <= n(n-1)/2，1 <= i, j <= n，i != j，0 < k <= 100
// 1 <= d <= m。
#include<bits/stdc++.h>
// 算法标签：最短路、Dijkstra
using namespace std;
const int MAXN = 101;
const int MAXM = 10001;

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};

priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);
int n,m,h,st,en;
int dis[MAXN][MAXN];
bool check[MAXN][MAXN];
int Dis[MAXN];
bool vis[MAXN];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            dis[i][j]=INT_MAX;
        }
    }
    for(int i=1;i<=n;i++){
        Dis[i]=INT_MAX;
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        dis[u][v]=w;
        dis[v][u]=w;
    }
    cin>>h;
    for(int i=1;i<=h;i++){
        int a,b;
        cin>>a>>b;
        check[a][b]=true;
        check[b][a]=true;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(dis[i][j]!=INT_MAX&&!check[i][j]){
                dis[i][j]=0;
            }
        }
    }
    cin>>st>>en;
    Dis[st]=0;
    heap.push({st,0});
    while(!heap.empty()){
        int u=heap.top().first;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=1;i<=n;i++){
            if(dis[i][u]!=INT_MAX){
                if(!vis[i]&&Dis[i]>Dis[u]+dis[i][u]){
                    Dis[i]=dis[i][u]+Dis[u];
                    heap.push({i,Dis[i]});
                }
            }
        }
    }
    cout<<Dis[en];
    return 0;
}
