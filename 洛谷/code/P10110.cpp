// https://www.luogu.com.cn/problem/P10110
// 题意：有 N 种商品和 M 条单向交换关系。
// 把商品 x 换成 y 要付 v[y]-v[x]+1 元。
// 给初始商品 a 和目标商品 b，求总花费最小值，无法到达输出 No solution。
// 数据范围：N ≤ 10^5，M ≤ 2 × 10^5，1 ≤ v[i] ≤ 10^9，编号在 [0, N-1]，a ≠ b，每次交换的两种商品不同。
// 算法标签：Dijkstra

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};

priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);
int n,m,st,en;
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
    cin>>n>>m>>st>>en;
    for(int i=0;i<n;i++){
        cin>>val[i];
    }
    for(int i=1,u,v,w;i<=m;i++){
        cin>>u>>v;
        w=1;

        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w;
        head[u]=cnt++;
    }
    for(int i=0;i<n;i++){
        dis[i]=INT_MAX;
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
    if(dis[en]==INT_MAX){
        cout<<"No solution";
    }else{
        cout<<-val[st]+val[en]+dis[en];
    }
    return 0;
}

