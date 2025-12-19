#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

// 定义边的结构体
struct Edge {
    int to, weight;  // 目标节点和边的权重
};

const int MAXN = 30010;  // 最大节点数
const int MAXK = 20;     // 最大rank级别（实际使用1-10）

vector<Edge> edges;      // 存储所有边的容器
vector<int> graph[MAXN]; // 图的邻接表，存储边的索引
vector<int> o_edge[MAXK]; // 按rank分组的节点列表
int n, m;               // 节点数和边数
int r[MAXN];            // 每个节点的rank值
int far[MAXK][MAXN];    // far[i][j]: 节点j到rank>=i的节点的最短距离
int dis[MAXN];          // 临时存储单源最短距离
bool vis[MAXN];         // 标记节点是否在队列中
bool ok[MAXN];          // 标记节点是否被当前源节点感兴趣
int ans = 0;            // 最终答案，所有|B(v)|之和

// 添加无向边到图中
void add_edge(int from, int to, int weight) {
    edges.push_back({to, weight});    // 添加正向边
    edges.push_back({from, weight});  // 添加反向边
    int idx = edges.size();           // 获取新添加边的索引
    graph[from].push_back(idx - 2);   // from节点指向正向边
    graph[to].push_back(idx - 1);     // to节点指向反向边
}

// 计算所有节点到rank>=x的节点的最短距离（多源最短路径）
void o_spfa(int x) {
    memset(vis, false, sizeof(vis));        // 初始化访问标记
    memset(far[x], 0x3f, sizeof(far[x]));   // 初始化距离为无穷大
    
    queue<int> q;
    // 将所有rank>=x的节点作为起点，距离设为0
    for (int u : o_edge[x]) {
        far[x][u] = 0;
        q.push(u);
        vis[u] = true;  // 标记为在队列中
    }
    
    // SPFA算法求多源最短路径
    while (!q.empty()) {
        int now = q.front(); 
        q.pop();
        vis[now] = false;  // 标记为不在队列中
        
        // 遍历当前节点的所有邻接边
        for (int idx : graph[now]) {
            const Edge& nxt = edges[idx];
            // 松弛操作：如果通过当前节点到达邻居的距离更短
            if (far[x][now] + nxt.weight < far[x][nxt.to]) {
                far[x][nxt.to] = far[x][now] + nxt.weight;
                // 如果邻居不在队列中，加入队列
                if (!vis[nxt.to]) {
                    vis[nxt.to] = true;
                    q.push(nxt.to);
                }
            }
        }
    }
}

// 优化far数组：far[i][x]应该是x到rank>=i的节点的最短距离
// 通过从高rank向低rank传递，确保far[i][x]包含所有更高rank的信息
void wk(int x) {
    for (int i = 1; i <= n; ++i) {
        // 取当前rank和更高rank的最小值
        if (far[x][i] > far[x + 1][i])
            far[x][i] = far[x + 1][i];
    }
}

// 对节点x执行SPFA，计算B(x)的大小（x感兴趣的节点数量）
void spfa(int x) {
    memset(vis, false, sizeof(vis));  // 初始化访问标记
    memset(dis, 0x3f, sizeof(dis));   // 初始化距离为无穷大
    memset(ok, false, sizeof(ok));    // 初始化感兴趣标记
    
    dis[x] = 0;           // 源节点距离为0
    vis[x] = true;        // 标记源节点在队列中
    queue<int> q; 
    q.push(x);            // 源节点入队
    
    while (!q.empty()) {
        int now = q.front(); 
        q.pop();
        vis[now] = false;  // 标记为不在队列中
        
        // 如果当前节点还没有被标记为感兴趣
        if (!ok[now]) {
            // 关键判断：当前节点now是否应该被源节点x感兴趣
            // 条件：不存在rank更高且距离更近的节点
            // 如果now的rank是10（最高），或者x到now的距离小于x到任何rank更高节点的距离
            if (dis[now] < far[r[x] + 1][now]) {
                ++ans;          // 增加总计数
                ok[now] = true; // 标记为感兴趣
            }
        }
        
        // 遍历当前节点的所有邻接边
        for (int idx : graph[now]) {
            const Edge& nxt = edges[idx];
            // 松弛操作
            if (dis[nxt.to] > dis[now] + nxt.weight) {
                dis[nxt.to] = dis[now] + nxt.weight;
                
                // 关键剪枝：只有当新节点可能被感兴趣时才加入队列
                // 条件：如果x的rank是10（最高），或者到新节点的距离小于到任何rank更高节点的距离
                if (!vis[nxt.to] && dis[nxt.to] < far[r[x] + 1][nxt.to]) {
                    q.push(nxt.to);
                    vis[nxt.to] = true;
                }
            }
        }
    }
}

int main() {
    // 读取节点数和边数
    scanf("%d%d", &n, &m);
    
    // 读取每个节点的rank值，并按rank分组存储
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &r[i]);
        o_edge[r[i]].push_back(i);  // 将节点加入对应rank的组
    }
    
    // 读取所有边并构建图
    for (int i = 1, u, v, t; i <= m; ++i) {
        scanf("%d%d%d", &u, &v, &t);
        add_edge(u, v, t);  // 添加无向边
    }
    
    // 预处理：计算每个rank级别的最短距离
    // 从rank=1到rank=10，计算到rank>=i的所有节点的最短距离
    for (int i = 1; i <= 10; ++i) {
        o_spfa(i);
    }
    
    // 优化far数组：确保far[i][x]包含所有rank>=i的信息
    // 从高rank向低rank传递最小值
    for (int i = 9; i >= 1; --i) {
        wk(i);
    }
    
    // 对每个节点执行SPFA，计算其感兴趣的节点数量
    for (int i = 1; i <= n; ++i) {
        spfa(i);
    }
    
    // 输出所有|B(v)|之和
    cout << ans;
    return 0;
}