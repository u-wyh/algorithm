// https://www.luogu.com.cn/problem/P10480
// 题意：给 N 个点、M 条有向边，保证图无环。
// 对每个点统计从它出发能到达的不同点数，包含自己。
// 输出：按点的编号逐行输出各点的答案。
// 数据范围：1 <= N, M <= 30000。
// 边的两个端点编号都在 [1, N]。
// 难度评分：1400（洛谷分级换算）
// 算法标签：拓扑排序、位集、分块

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30005;
const int MAXM = 30005;
const int BLOCK = 1024;

int n, m;
int head[MAXN], nextEdge[MAXM], to[MAXM], edgeCount;
int degree[MAXN], order[MAXN], ans[MAXN];
bitset<BLOCK> reachable[MAXN];

void toposort(){
    int count = 0;
    for (int i = 1; i <= n; ++i){
        if (degree[i] == 0){
            order[count++] = i;
        }
    }
    for (int i = 0; i < count; ++i){
        int u = order[i];
        for (int edge = head[u]; edge; edge = nextEdge[edge]){
            int v = to[edge];
            if (--degree[v] == 0){
                order[count++] = v;
            }
        }
    }
}

void countReachable(){
    // 每轮只保存一段目标编号的可达位集。
    for (int first = 1; first <= n; first += BLOCK){
        int last = min(n, first + BLOCK - 1);
        for (int i = n - 1; i >= 0; --i){
            int u = order[i];
            auto& state = reachable[u];
            state.reset();
            if (first <= u && u <= last){
                state.set(u - first);
            }
            for (int edge = head[u]; edge; edge = nextEdge[edge]){
                state |= reachable[to[edge]];
            }
            ans[u] += state.count();
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; ++i){
        int u, v;
        cin >> u >> v;
        ++degree[v];
        nextEdge[++edgeCount] = head[u];
        head[u] = edgeCount;
        to[edgeCount] = v;
    }

    toposort();
    countReachable();
    for (int u = 1; u <= n; ++u){
        cout << ans[u] << '\n';
    }
    return 0;
}
