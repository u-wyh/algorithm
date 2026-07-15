#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stack>
using namespace std;

const int MAXN = 200000;
const int MAXM = 400000;
const int MAXQ = 200000;
const int MAXT = 400000; // 2 * MAXN
const int LOGN = 18;

struct Edge {
    int u, v, w;
} edges[MAXM];

int n, m, q;

// 人形树相关
int tot1;
vector<int> tree1[MAXT];
int w1[MAXT];
int f1[MAXT][LOGN], depth1[MAXT];
int in1[MAXT], out1[MAXT];
int dfn1[MAXN];
int dfn1_cnt;
int fa1[MAXT];

int find1(int x) {
    return fa1[x] == x ? x : fa1[x] = find1(fa1[x]);
}

// 狼形树相关
int tot2;
vector<int> tree2[MAXT];
int w2[MAXT];
int f2[MAXT][LOGN], depth2[MAXT];
int in2[MAXT], out2[MAXT];
int dfn2[MAXN];
int dfn2_cnt;
int fa2[MAXT];

int find2(int x) {
    return fa2[x] == x ? x : fa2[x] = find2(fa2[x]);
}

// 二维数点相关
struct Point {
    int x, y; // x=dfn1[i], y=dfn2[i]
} points[MAXN];

struct Event {
    int x;
    int id;
    int type;
    int l, r;
};

vector<Event> events;
int ans[MAXQ];

// 树状数组
int tree_bit[MAXN + 10];

inline int lowbit(int x) {
    return x & -x;
}

void add_bit(int pos, int val) {
    for (; pos <= n; pos += lowbit(pos))
        tree_bit[pos] += val;
}

int query_bit(int pos) {
    int res = 0;
    for (; pos; pos -= lowbit(pos))
        res += tree_bit[pos];
    return res;
}

int query_range_bit(int l, int r) {
    if (l > r) return 0;
    return query_bit(r) - query_bit(l - 1);
}

void build_tree1() {
    tot1 = n;
    for (int i = 0; i < 2 * n; i++) {
        fa1[i] = i;
    }
    for (int i = 0; i < n; i++) {
        w1[i] = i;
    }
    sort(edges, edges + m, [](const Edge& a, const Edge& b) {
        return a.w > b.w;
    });
    for (int i = 0; i < m; i++) {
        int u = edges[i].u, v = edges[i].v;
        int ru = find1(u), rv = find1(v);
        if (ru == rv) continue;
        w1[tot1] = edges[i].w;
        tree1[tot1].push_back(ru);
        tree1[tot1].push_back(rv);
        fa1[ru] = fa1[rv] = tot1;
        tot1++;
    }
}

void dfs1(int root) {
    stack<int> st;
    st.push(root);
    depth1[root] = 0;
    f1[root][0] = -1;
    vector<bool> visited(tot1, false);
    vector<int> children_processed(tot1, 0);
    while (!st.empty()) {
        int u = st.top();
        if (!visited[u]) {
            visited[u] = true;
            if (u < n) {
                dfn1[u] = ++dfn1_cnt;
                in1[u] = dfn1[u];
                out1[u] = dfn1[u];
            } else {
                in1[u] = n + 1;
                out1[u] = 0;
            }
            for (int i = 0; i < tree1[u].size(); i++) {
                int v = tree1[u][i];
                if (v == f1[u][0]) continue;
                depth1[v] = depth1[u] + 1;
                f1[v][0] = u;
                st.push(v);
            }
        } else {
            st.pop();
            for (int v : tree1[u]) {
                if (v == f1[u][0]) continue;
                in1[u] = min(in1[u], in1[v]);
                out1[u] = max(out1[u], out1[v]);
            }
        }
    }
}

void build_tree2() {
    tot2 = n;
    for (int i = 0; i < 2 * n; i++) {
        fa2[i] = i;
    }
    for (int i = 0; i < n; i++) {
        w2[i] = i;
    }
    sort(edges, edges + m, [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });
    for (int i = 0; i < m; i++) {
        int u = edges[i].u, v = edges[i].v;
        int ru = find2(u), rv = find2(v);
        if (ru == rv) continue;
        w2[tot2] = edges[i].w;
        tree2[tot2].push_back(ru);
        tree2[tot2].push_back(rv);
        fa2[ru] = fa2[rv] = tot2;
        tot2++;
    }
}

void dfs2(int root) {
    stack<int> st;
    st.push(root);
    depth2[root] = 0;
    f2[root][0] = -1;
    vector<bool> visited(tot2, false);
    while (!st.empty()) {
        int u = st.top();
        if (!visited[u]) {
            visited[u] = true;
            if (u < n) {
                dfn2[u] = ++dfn2_cnt;
                in2[u] = dfn2[u];
                out2[u] = dfn2[u];
            } else {
                in2[u] = n + 1;
                out2[u] = 0;
            }
            for (int i = 0; i < tree2[u].size(); i++) {
                int v = tree2[u][i];
                if (v == f2[u][0]) continue;
                depth2[v] = depth2[u] + 1;
                f2[v][0] = u;
                st.push(v);
            }
        } else {
            st.pop();
            for (int v : tree2[u]) {
                if (v == f2[u][0]) continue;
                in2[u] = min(in2[u], in2[v]);
                out2[u] = max(out2[u], out2[v]);
            }
        }
    }
}

void pre_lca1() {
    for (int j = 1; j < LOGN; j++) {
        for (int i = 0; i < tot1; i++) {
            if (f1[i][j - 1] != -1) {
                f1[i][j] = f1[f1[i][j - 1]][j - 1];
            } else {
                f1[i][j] = -1;
            }
        }
    }
}

void pre_lca2() {
    for (int j = 1; j < LOGN; j++) {
        for (int i = 0; i < tot2; i++) {
            if (f2[i][j - 1] != -1) {
                f2[i][j] = f2[f2[i][j - 1]][j - 1];
            } else {
                f2[i][j] = -1;
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        edges[i] = {u, v, min(u, v)};
    }

    // 构建人形树
    build_tree1();
    int root1 = tot1 - 1;
    memset(f1, -1, sizeof(f1));
    dfn1_cnt = 0;
    dfs1(root1);
    pre_lca1();

    // 为狼形树准备边权
    for (int i = 0; i < m; i++) {
        edges[i].w = max(edges[i].u, edges[i].v);
    }

    // 构建狼形树
    build_tree2();
    int root2 = tot2 - 1;
    memset(f2, -1, sizeof(f2));
    dfn2_cnt = 0;
    dfs2(root2);
    pre_lca2();

    // 设置二维点
    for (int i = 0; i < n; i++) {
        points[i] = {dfn1[i], dfn2[i]};
    }

    // 处理查询
    for (int i = 0; i < q; i++) {
        int S, E, L, R;
        scanf("%d%d%d%d", &S, &E, &L, &R);
        // 在人形树上找A
        int A = S;
        for (int j = LOGN - 1; j >= 0; j--) {
            if (f1[A][j] != -1 && w1[f1[A][j]] >= L) {
                A = f1[A][j];
            }
        }
        // 在狼形树上找B
        int B = E;
        for (int j = LOGN - 1; j >= 0; j--) {
            if (f2[B][j] != -1 && w2[f2[B][j]] <= R) {
                B = f2[B][j];
            }
        }
        // 添加事件
        events.push_back({out1[A], i, 1, in2[B], out2[B]});
        events.push_back({in1[A] - 1, i, -1, in2[B], out2[B]});
    }

    // 排序事件
    sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        return a.x < b.x;
    });
    // 排序点
    sort(points, points + n, [](const Point& a, const Point& b) {
        return a.x < b.x;
    });

    // 处理二维数点
    memset(tree_bit, 0, sizeof(tree_bit));
    int j = 0;
    for (const Event& e : events) {
        while (j < n && points[j].x <= e.x) {
            add_bit(points[j].y, 1);
            j++;
        }
        int tmp = query_range_bit(e.l, e.r);
        ans[e.id] += e.type * tmp;
    }

    // 输出结果
    for (int i = 0; i < q; i++) {
        printf("%d\n", ans[i] > 0 ? 1 : 0);
    }

    return 0;
}