// https://www.luogu.com.cn/problem/P10535
// 题意：有 n 类、共 2n 种接口，只有 i 和 n+i 能相扣。
// 给 m 种可重复购买的双向线，每种给两端接口和价格。
// 求把接口 S 和 T 的电器连通的最低费用，
// 无解输出 I have no idea how to solve it.。
// 数据范围：1 ≤ n,m ≤ 10^5，接口编号在 [1,2n]，
// 1 ≤ w[i] ≤ 10^9。
// 算法标签：Dijkstra

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXM = 5e5+5;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;

int n,m,st,en;

long dis[MAXN];
auto compare = [](const pair<int, long>& left, const pair<int, long>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};
priority_queue<pair<int, long>, vector<pair<int, long>>, decltype(compare)> heap(compare);
//初始化建立小根堆
bool vis[MAXN];

void addEdge(int u, int v, int w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void build(){
    for(int i=1;i<=n;i++){
        addEdge(i,i+n,0);
        addEdge(i+n,i,0);
        dis[i]=LONG_MAX;
        dis[i+n]=LONG_MAX;
    }
}

void dijkstra() {
    heap.push({ st, 0 });
    dis[st] = 0;
    int u;
    long w;
    while (!heap.empty()) {
        u=heap.top().first;
        w=heap.top().second;
        heap.pop();
        if (vis[u]) {
            continue;
        }
        vis[u] = true;
        if(u==en)
            break;
        for (int ei = head[u], v; ei > 0; ei = Next[ei]) {
            v = to[ei];
            if (!vis[v] && dis[v] > w + weight[ei]) {
                dis[v] = w + weight[ei];
                heap.push({ v, dis[v] });
            }
        }
    }
}


int main()
{
    cin>>n>>m;
    build();
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    cin>>st>>en;
    dijkstra();
    if(dis[en]==LONG_MAX)
        cout<<"I have no idea how to solve it.";
    else
        cout<<dis[en];
    return 0;
}
