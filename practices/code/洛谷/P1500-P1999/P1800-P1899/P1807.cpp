// https://www.luogu.com.cn/problem/P1807
// 题意：给定 n 个点和 m 条带权有向边，图中没有环。
// 求从 1 到 n 的路径中边权和最大是多少，若不可达输出 -1。
// 数据范围：1 ≤ n ≤ 1500，0 ≤ m ≤ 5×10^4，
// 1 ≤ u,v ≤ n，−10^5 ≤ w ≤ 10^5。
// 难度评分：1300（洛谷分级换算）
// 算法标签：Dijkstra、最短路

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1501;
const int MAXM = 50001;

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second;
};

priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);
int n,m;
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;
bool vis[MAXN];
int dis[MAXN];

int main()
{
    cin>>n>>m;
    for(int i=1,u,v,w;i<=m;i++){
        cin>>u>>v>>w;
        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=-w;
        head[u]=cnt++;
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
                dis[v]=w+dis[u];
                heap.push({v,dis[v]});
            }
        }
    }
    if(dis[n]=INT_MAX)
        dis[n]=1;
    cout<<dis[n];
    return 0;
}
