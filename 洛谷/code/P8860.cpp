#include <algorithm>
#include <queue>
#include <vector>
#include <utility>
#include <cctype>
#include <cstdio>

using namespace std;

const int N = 200050;

// 图的存储结构
int pre[N];    // pre[i]: 以节点i为起点的第一条边的编号
int nxt[N];    // nxt[i]: 编号为i的边的下一条同起点的边
int fr[N];     // fr[i]: 编号为i的边的起点
int to[N];     // to[i]: 编号为i的边的终点
int a[N];      // a[i]: 编号为i的边被删除的时间（初始为q，表示未被删除）
int fa[N];     // fa[i]: 节点i在关键路径上的前驱边编号
bool rm[N];    // rm[i]: 第i次查询是否删除了边

// 快速读入函数
int read() {
    int ans = 0, c;
    while (!isdigit(c = getchar()));
    do ans = ans * 10 + c - '0';
    while (isdigit(c = getchar()));
    return ans;
}

int main() {
    // 读入点数n，边数m，查询数q
    int n = read(), m = read(), q = read();
    
    // 读入m条边，构建邻接表
    for (int i = 1; i <= m; ++i) {
        fr[i] = read();  // 读入边的起点
        to[i] = read();  // 读入边的终点
        nxt[i] = pre[fr[i]];  // 将当前边插入到起点的邻接表头部
        pre[fr[i]] = i;       // 更新起点的第一条边
        a[i] = q;             // 初始化边的删除时间为q（表示未被删除）
    }
    
    // 处理q个查询
    for (int i = 0; i < q; ++i) {
        int x = read();  // 读入要尝试删除的边编号
        if (a[x] > i) {  // 如果这条边之前没有被标记过删除时间
            a[x] = i;    // 记录删除时间为当前查询索引
            rm[i] = true; // 标记这个查询会删除这条边
        }
    }
    
    // 添加一条虚拟边，从虚拟节点0到节点1，用于统一处理
    fr[m + 1] = 0;
    to[m + 1] = 1;
    a[m + 1] = 0;  // 虚拟边的删除时间为0（最早）
    
    // 使用优先队列（最大堆）进行类似Dijkstra的算法
    // 优先队列元素为(边的删除时间, 边的编号)
    priority_queue<pair<int, int>> Q;
    Q.push({a[m + 1], m + 1});  // 从虚拟边开始
    
    // 寻找关键路径
    while (!Q.empty()) {
        auto [d, e] = Q.top();  // 获取当前删除时间最大的边
        Q.pop();
        int u = to[e];  // 获取这条边的终点
        if (fa[u]) continue;  // 如果这个节点已经被访问过，跳过
        fa[u] = e;      // 记录这个节点的前驱边
        // 遍历从这个节点出发的所有边
        for (int i = pre[u]; i; i = nxt[i]) {
            Q.push({a[i], i});  // 将边加入优先队列
        }
    }
    
    // 回溯关键路径，将路径上的边标记为不可删除
    for (int i = n; i != 1; i = fr[fa[i]]) {
        int e = fa[i];  // 获取节点i的前驱边
        if (a[e] < q) { // 如果这条边有删除时间（不是初始值q）
            rm[a[e]] = false;  // 标记这条边不会被删除
        }
    }
    
    // 输出每个查询的结果
    for (int i = 0; i < q; ++i) {
        printf("%d\n", rm[i] ? 1 : 0);
    }
    
    return 0;
} 