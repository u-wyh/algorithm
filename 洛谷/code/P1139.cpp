// https://www.luogu.com.cn/problem/P1139
// 题意：入口 A 左侧有 n 辆火车按 a, b, c... 编号等待进站，右侧为出口 D。
// 题意：中间有 B、C 两个不限容量的调度站，火车仅可从左向右单向移动。
// 题意：给出目标出站顺序（出口 D 从左到右的序列），求调度操作方案。
// 输入：输入整数 n 及由前 n 个小写字母构成的目标排列字符串。
// 输出：有解输出最短操作序列，多解时输出 (L, R) 字典序最小方案，每行 h L R。
// 输出：若无法完成调度，输出 NO。
// 数据范围：1 < n <= 15。
#include<bits/stdc++.h>
// 算法标签：最短路、Dijkstra、优先队列
using namespace std;
const int MAXN = 2505;
const int MAXM = 15005;

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
int n,m,s,en;

int main()
{
    cin>>n>>m>>s>>en;
    graph.resize(n+1);
    for(int i=1;i<=m;i++){
        cin>>edge[i][0]>>edge[i][1]>>edge[i][2];
        graph[edge[i][0]].push_back({edge[i][1],edge[i][2]});
        graph[edge[i][1]].push_back({edge[i][0],edge[i][2]});
    }
    //初始化建图

    for(int i=1;i<=n;i++){
        Distance[i]=INT_MAX;
    }
    //将数组初始化

    Distance[s]=0;
    //以s点作为源点传输信号
    heap.push({s,0});
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
    cout<<Distance[en];
    return 0;
}

