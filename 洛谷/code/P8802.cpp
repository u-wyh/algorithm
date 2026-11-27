// https://www.luogu.com.cn/problem/P8802
// 题意：输入 N 个城市、M 条带权双向边 (u, v, c) 以及到达每个城市 i 需额外隔离的时间 C_i（起点 1 和终点 N 不计隔离时间）；
// 输出从城市 1 到城市 N 的最短总耗时。
// 数据范围：1 <= N <= 1000，1 <= M <= 10000，1 <= C_i <= 200，1 <= u, v <= N
// 1 <= c <= 1000。
// 算法标签：Dijkstra、最短路、优先队列
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXM = 20005;

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};

priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);
int n,m;
int arr[MAXN];
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;
int dis[MAXN];
bool vis[MAXN];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    for(int i=1,u,v,w;i<=m;i++){
        cin>>u>>v>>w;
        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w+arr[v];
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        weight[cnt]=w+arr[u];
        head[v]=cnt++;
    }
    for(int i=1;i<=n;i++){
        dis[i]=INT_MAX;
    }
    dis[1]=0;
    heap.push({1,0});
    while(!heap.empty()){
        int u=heap.top().first;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=head[u];i>0;i=Next[i]){
            int v=to[i];
            int w=weight[i];
            if(!vis[v]&&dis[u]<dis[v]-w){
                dis[v]=dis[u]+w;
                heap.push({v,dis[v]});
            }
        }
    }
    cout<<dis[n]-arr[n];
    return 0;
}
