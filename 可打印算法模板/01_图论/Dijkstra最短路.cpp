// 用途：有向非负权图单源最短路；输入 n m s 和 m 条 u v w。
// 时间：O((n+m) log m)。
// 空间：O(n+m)。
// 注意：不可达输出 -1；n<=1e5，m<=2e5；提交例题时按题面改输出。
// 例题：https://www.luogu.com.cn/problem/P4779
// 题意：求非负边权有向图中起点到各点的最短距离。
// 思路：优先队列每次取当前最近点，沿出边松弛。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXM = 200005;
const long long INF = LLONG_MAX / 4;

int n, m, s, head[MAXN], to[MAXM], nxt[MAXM], cnt;
long long weight[MAXM], dista[MAXN];
struct Item { long long d; int u; } heapArr[MAXM + 5];
int heapSize;

void push(Item x) {
    int i = ++heapSize;
    while (i > 1 && heapArr[i / 2].d > x.d) {
        heapArr[i] = heapArr[i / 2];
        i /= 2;
    }
    heapArr[i] = x;
}

Item pop() {
    Item ret = heapArr[1], x = heapArr[heapSize--];
    if (heapSize) {
        int i = 1;
        while (i * 2 <= heapSize) {
            int j = i * 2;
            if (j < heapSize && heapArr[j + 1].d < heapArr[j].d) ++j;
            if (heapArr[j].d >= x.d) break;
            heapArr[i] = heapArr[j];
            i = j;
        }
        heapArr[i] = x;
    }
    return ret;
}

void addEdge(int u, int v, long long w) {
    to[++cnt] = v;
    weight[cnt] = w;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

void dijkstra() {
    fill(dista + 1, dista + n + 1, INF);
    dista[s] = 0;
    push({0, s});
    while (heapSize) {
        Item item = pop();
        long long d = item.d;
        int u = item.u;
        // 堆里允许旧距离；只扩展当前最短状态。
        if (d != dista[u]) continue;
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            long long nd = d + weight[e];
            if (nd < dista[v]) {
                dista[v] = nd;
                push({nd, v});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (!(cin >> n >> m >> s)) return 0;
    for (int i = 0, u, v; i < m; ++i) {
        long long w;
        cin >> u >> v >> w;
        addEdge(u, v, w);
    }
    dijkstra();
    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << ' ';
        cout << (dista[i] == INF ? -1 : dista[i]);
    }
    cout << '\n';
    return 0;
}
