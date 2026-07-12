#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 100;
const int MAXM = 10000;
const int INF = 1e18;

struct Person {
    int x, y;
    string name;
};

int k, n;
int S, T;
int node_cnt;

Person people[70];
unordered_map<string, int> id;
int val[35][35];

int head[MAXN], nxt[MAXM], to[MAXM], cap[MAXM], cost[MAXM];
int cnt = 2;

int pot[MAXN], dis[MAXN], pre[MAXN];
bool inq[MAXN], vis[MAXN];

int maxflow, mincost;

queue<int> q;

struct cmp {
    bool operator()(pair<int, int> a, pair<int, int> b) {
        return a.first > b.first;
    }
};

priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> heap;

// 将名字统一转为小写，题目要求忽略大小写
string norm(string s) {
    for (char &c : s) {
        c = tolower(c);
    }
    return s;
}

// 叉积：判断三点是否共线
int cross(const Person &a, const Person &b, const Person &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// 判断点 c 是否在线段 ab 上
bool onSegment(const Person &a, const Person &b, const Person &c) {
    if (cross(a, b, c) != 0) return false;

    return min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x)
        && min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y);
}

// 添加费用流边
void addedge(int u, int v, int w, int c) {
    // 正向边：容量 w，费用 c
    nxt[cnt] = head[u];
    to[cnt] = v;
    cap[cnt] = w;
    cost[cnt] = c;
    head[u] = cnt++;

    // 反向边：容量 0，费用 -c
    nxt[cnt] = head[v];
    to[cnt] = u;
    cap[cnt] = 0;
    cost[cnt] = -c;
    head[v] = cnt++;
}

// 初始 SPFA，计算势能 pot
void spfa(int s) {
    for (int i = 0; i <= node_cnt; i++) {
        pot[i] = INF;
        inq[i] = false;
    }

    pot[s] = 0;
    q.push(s);
    inq[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;

        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];

            if (cap[i] > 0 && pot[u] + cost[i] < pot[v]) {
                pot[v] = pot[u] + cost[i];

                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
        }
    }
}

// Dijkstra 找当前最短费用增广路
bool dijkstra() {
    for (int i = 0; i <= node_cnt; i++) {
        dis[i] = INF;
        pre[i] = -1;
        vis[i] = false;
    }

    while (!heap.empty()) heap.pop();

    dis[S] = 0;
    heap.push({0, S});

    while (!heap.empty()) {
        int u = heap.top().second;
        heap.pop();

        if (vis[u]) continue;
        vis[u] = true;

        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];

            if (cap[i] <= 0) continue;

            // Johnson 重新标号后的费用
            int adjusted_cost = cost[i] + pot[u] - pot[v];

            if (dis[u] + adjusted_cost < dis[v]) {
                dis[v] = dis[u] + adjusted_cost;
                pre[v] = i;
                heap.push({dis[v], v});
            }
        }
    }

    return dis[T] < INF;
}

// 最小费用最大流
void mincostmaxflow() {
    maxflow = 0;
    mincost = 0;

    spfa(S);

    while (dijkstra()) {
        int flow = INF;

        // 找这条增广路上能增广的最小容量
        for (int u = T; u != S; u = to[pre[u] ^ 1]) {
            flow = min(flow, cap[pre[u]]);
        }

        maxflow += flow;

        // 当前路径真实费用 = dis[T] + pot[T] - pot[S]
        // 这里 pot[S] 通常是 0，所以写 dis[T] + pot[T]
        mincost += flow * (dis[T] + pot[T]);

        // 更新残量网络
        for (int u = T; u != S; u = to[pre[u] ^ 1]) {
            cap[pre[u]] -= flow;
            cap[pre[u] ^ 1] += flow;
        }

        // 更新势能
        for (int i = 0; i <= node_cnt; i++) {
            if (dis[i] < INF) {
                pot[i] += dis[i];
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> k;
    cin >> n;

    // 读入所有人
    // 0 ~ n - 1 是男生
    // n ~ 2n - 1 是女生
    for (int i = 0; i < 2 * n; i++) {
        cin >> people[i].x >> people[i].y >> people[i].name;
        people[i].name = norm(people[i].name);
        id[people[i].name] = i;
    }

    // 默认缘分值为 1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            val[i][j] = 1;
        }
    }

    // 读入特殊缘分值
    string a, b;
    while (cin >> a) {
        if (a == "End") break;

        int p;
        cin >> b >> p;

        a = norm(a);
        b = norm(b);

        int u = id[a];
        int v = id[b];

        // 保证 u 是男生，v 是女生
        if (u >= n && v < n) {
            swap(u, v);
        }

        if (u < n && v >= n) {
            val[u][v - n] = p;
        }
    }

    S = 2 * n;
    T = 2 * n + 1;
    node_cnt = 2 * n + 1;

    // 源点连男生
    for (int i = 0; i < n; i++) {
        addedge(S, i, 1, 0);
    }

    // 女生连汇点
    for (int j = 0; j < n; j++) {
        addedge(n + j, T, 1, 0);
    }

    int limit = k * k;

    // 枚举每个男生和女生，判断是否可以射箭
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int woman = n + j;

            int dx = people[i].x - people[woman].x;
            int dy = people[i].y - people[woman].y;

            // 距离超过射程，不能连边
            if (dx * dx + dy * dy > limit) continue;

            bool blocked = false;

            // 判断两人之间是否有其他人挡住
            for (int t = 0; t < 2 * n; t++) {
                if (t == i || t == woman) continue;

                if (onSegment(people[i], people[woman], people[t])) {
                    blocked = true;
                    break;
                }
            }

            if (!blocked) {
                // 因为模板是最小费用流，所以最大缘分值转成最小负费用
                addedge(i, woman, 1, -val[i][j]);
            }
        }
    }

    mincostmaxflow();

    // mincost 是负数，取反就是最大缘分值
    cout << -mincost << '\n';

    return 0;
}