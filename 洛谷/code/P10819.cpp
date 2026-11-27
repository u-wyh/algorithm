// https://www.luogu.com.cn/problem/P10819
// 题意：
// 给定 n 点 m 边无向图（可能有重边），初始每条边限速 1 m/s，通过限速为 a 的边耗时 1/a 秒。
// 共有 k 美元，每花 1 美元可使某条边限速永久提高 1 m/s（每边可分配任意非负整数金额）。
// 给定两对起终点 (s1, t1) 与 (s2, t2)，合理分配资金使两者的最短旅行时间之和最小。
// 输出最小时间之和（绝对或相对误差不超过 10^-9 均算正确）。
// 数据范围：
// 1 <= n <= 5000
// 0 <= m <= 5000
// 0 <= k <= 10^9
// 1 <= a, b, s1, t1, s2, t2 <= n（a != b）
// 算法标签：广度优先搜索、三分搜索
#include <bits/stdc++.h>
using namespace std;

const int N = 5005;
const int inf = 1e9;

int h[N], e[N*2], nxt[N*2], idx;
int dis[N][N];
int n, m, k;
int s1, t1, s2, t2;
int path[N];
double ans;

void add(int u, int v) {
    e[idx] = v;
    nxt[idx] = h[u];
    h[u] = idx++;
}

void bfs(int s) {
    for (int i = 1; i <= n; ++i) {
        dis[s][i] = (i == s) ? 0 : inf;
    }
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = h[u]; ~i; i = nxt[i]) {
            int v = e[i];
            if (dis[s][v] == inf) {
                dis[s][v] = dis[s][u] + 1;
                q.push(v);
            }
        }
    }
}

double calc(int tot, int val) {
    if (tot == 0) return 0.0;
    if (val == 0) return (double)tot;
    int ave = val / tot;
    int lef = val % tot;
    return (double)(tot - lef) / (ave + 1) + (double)lef / (ave + 2);
}

double check(int sha, int idv, int mid) {
    return 2.0 * calc(sha, mid) + calc(idv, k - mid);
}

double solve(int sha, int idv) {
    int l = 0, r = k;
    double ret = 1e30;
    while (l <= r) {
        int lmid = l + (r - l) / 3;
        int rmid = r - (r - l) / 3;
        double lval = check(sha, idv, lmid);
        double rval = check(sha, idv, rmid);
        if (lval < rval) {
            r = rmid - 1;
            ret = min(ret, lval);
        } else {
            l = lmid + 1;
            ret = min(ret, rval);
        }
    }
    return ret;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    memset(h, -1, sizeof h);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    scanf("%d%d%d%d", &s1, &t1, &s2, &t2);
    
    for (int i = 1; i <= n; ++i) {
        bfs(i);
    }
    
    for (int i = 0; i <= n; ++i) {
        path[i] = inf;
    }
    
    for (int u = 1; u <= n; ++u) {
        for (int v = 1; v <= n; ++v) {
            if (dis[u][v] != inf) {
                if (dis[s1][u] != inf && dis[s2][u] != inf && dis[v][t1] != inf && dis[v][t2] != inf) {
                    int total = dis[s1][u] + dis[s2][u] + dis[v][t1] + dis[v][t2];
                    if (total < path[dis[u][v]]) {
                        path[dis[u][v]] = total;
                    }
                }
                if (dis[s1][u] != inf && dis[t2][u] != inf && dis[v][t1] != inf && dis[v][s2] != inf) {
                    int total = dis[s1][u] + dis[t2][u] + dis[v][t1] + dis[v][s2];
                    if (total < path[dis[u][v]]) {
                        path[dis[u][v]] = total;
                    }
                }
            }
        }
    }
    
    ans = check(0, dis[s1][t1] + dis[s2][t2], 0);
    for (int i = 0; i <= n; ++i) {
        if (path[i] != inf) {
            double current = solve(i, path[i]);
            if (current < ans) {
                ans = current;
            }
        }
    }
    
    printf("%.20lf\n", ans);
    
    return 0;
}