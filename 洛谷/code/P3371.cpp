// https://www.luogu.com.cn/problem/P3371
// 题意：给一张有向图，有 n 个点、m 条边，出发点为 s。
// 每条边用 (u, v, w) 表示，可以从 u 走到 v，距离为 w。两点之间可能有多条边。
// 按点编号输出从 s 到每个点的最短距离。走不到的点输出 2^31 - 1。
// 数据范围：1 ≤ n ≤ 10^4，1 ≤ m ≤ 5 × 10^5，1 ≤ u, v ≤ n，w ≥ 0，所有边权之和小于 2^31。

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10005;
const int MAXM = 500005;

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};

priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);
int n,m,st;
int val[MAXN];
int dis[MAXN];
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;
bool vis[MAXN];

int main()
{
    cin>>n>>m>>st;
    for(int i=1,u,v,w;i<=m;i++){
        cin>>u>>v>>w;
        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w;
        head[u]=cnt++;
    }
    for(int i=1;i<=n;i++){
        dis[i]=pow(2,31)-1;
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
        for(int i=head[u];i>0;i=Next[i]){
            int v=to[i];
            int w=weight[i];
            if(!vis[v]&&dis[u]<dis[v]-w){
                dis[v]=w+dis[u];
                heap.push({v,dis[v]});
            }
        }
    }
    for(int i=1;i<=n;i++){
        cout<<dis[i]<<' ';
    }
    return 0;
}


