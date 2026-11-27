// https://www.luogu.com.cn/problem/P2951
// 题意：输入谷仓数 N、无向边数 M，
// 以及 M 条连接 A_i 与 B_i
// 的无向边（边权均为 1，起点为 1 号谷仓）。
// 计算所有谷仓到 1 号谷仓的最短路径长度，找出距离最大的谷仓。
// 若有多个谷仓并列最远，
// 记录编号最小的谷仓编号、该最远距离、以及达到该最远距离的谷仓总数。
// 输出一行三个用空格隔开的整数：最远谷仓的最小编号、最远距离、满足该距离的谷仓数。
// 数据范围：对于 100% 的数据，2 <= n <= 50000，
// 1 <= m <= 50000。
// 算法标签：最短路、Dijkstra、优先队列
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 20005;
const int MAXM = 100005;

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};

priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);
int n,m;
int dis[MAXN];
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;
bool vis[MAXN];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w=1;
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        weight[cnt]=w;
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
                dis[v]=w+dis[u];
                heap.push({v,dis[v]});
            }
        }
    }
    int ans1=0,ans2=0,ans3=0;
    for(int i=2;i<=n;i++){
        if(dis[i]>ans1&&dis[i]!=INT_MAX){
            ans1=dis[i];
            ans2=i;
            ans3=0;
        }
        if(ans1=dis[i]){
            ans3++;
        }
    }
    cout<<ans2<<' '<<ans1<<' '<<ans3;
    return 0;
}

