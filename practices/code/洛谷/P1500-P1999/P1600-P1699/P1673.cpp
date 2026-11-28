// https://www.luogu.com.cn/problem/P1673
// 题意：按顺序经过 N 颗行星，每颗行星可把货物 A_i 换成 B_i，
// 也可以跳过这次交易。
// 从货物 1 出发，求换到 K 最少经手几种货物，起点和终点也计入。
// 换不到输出 -1。
// 数据范围：1 ≤ N ≤ 5×10^4，1 ≤ K ≤ 1000，
// 货物编号在 [1,K]。
// 难度评分：1300（洛谷分级换算）
// 算法标签：Dijkstra、最短路、优先队列

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXM = 50005;

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};

priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);
//初始化建立小根堆
vector<vector<pair<int ,int >>>graph;
//邻接表建图
int edge[MAXM][3];
int Distance[MAXN];
//记录到源点的最小距离
bool visit[MAXN];
//记录这个点是否被访问过
int n,m;

int main()
{
    cin>>m>>n;
    graph.resize(n+1);
    for(int i=1;i<=m;i++){
        cin>>edge[i][0]>>edge[i][1];
        graph[edge[i][0]].push_back({edge[i][1],1});
    }
    //初始化建图

    for(int i=1;i<=n;i++){
        Distance[i]=INT_MAX;
    }
    //将数组初始化

    Distance[1]=0;
    //以s点作为源点传输信号
    heap.push({1,0});
    //小根堆储存的形式是  节点——权值  以权值建堆
    while(!heap.empty()){
        int u=heap.top().first;
        heap.pop();
        if(visit[u]){
            continue;
        }
        visit[u]=true;
        for(int i=0;i<graph[u].size();i++){
            int v=graph[u][i].first;
            int w=graph[u][i].second;
            if(!visit[v]&&(w+Distance[u])<Distance[v]){
                Distance[v]=w+Distance[u];
                heap.push({v,Distance[u]+w});
            }
        }
    }
    if(Distance[n]==INT_MAX)
        cout<<-1;
    else
        cout<<Distance[n]+1;
    return 0;
}


