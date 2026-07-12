#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000 + 5;
const int MAXM = MAXN << 1;
const long long NEG = -(1LL << 60);

int n;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];
int cntg = 1;

int parent[MAXN];
int order[MAXN];
int orderCnt;

long long down0[MAXN];
long long down1[MAXN];

long long up0[MAXN];
long long up1[MAXN];

long long answer;

inline void addedge(int u, int v, int w) {
    nxt[cntg] = head[u];
    to[cntg] = v;
    weight[cntg] = w;
    head[u] = cntg++;
}

// 以 1 为临时根，确定每个点的父亲和遍历顺序
void buildTree() {
    order[++orderCnt] = 1;

    for (int i = 1; i <= orderCnt; i++) {
        int u = order[i];

        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];

            if (v == parent[u]) {
                continue;
            }

            parent[v] = u;
            order[++orderCnt] = v;
        }
    }
}

// 从叶子向上计算 down0、down1
void calcDown() {
    for (int i = orderCnt; i >= 1; i--) {
        int u = order[i];

        long long sum = 0;
        long long bestGain = NEG;

        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            int w = weight[e];

            if (v == parent[u]) {
                continue;
            }

            long long base = max(
                down0[v],
                down1[v] + w
            );

            long long gain =
                down0[v] + w - base;

            sum += base;
            bestGain = max(bestGain, gain);
        }

        down0[u] = sum;

        if (bestGain == NEG) {
            down1[u] = NEG;
        } else {
            down1[u] = sum + bestGain;
        }
    }
}

// 换根，计算父亲方向的信息，并统计每个点作为根时的答案
void reroot() {
    up0[1] = 0;
    up1[1] = NEG;

    answer = 0;

    for (int i = 1; i <= orderCnt; i++) {
        int u = order[i];

        long long total = 0;

        long long best1 = NEG;
        long long best2 = NEG;
        int bestFrom = -1;

        // 计算所有相邻方向的总贡献
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            int w = weight[e];

            long long f0;
            long long f1;

            if (v == parent[u]) {
                f0 = up0[u];
                f1 = up1[u];
            } else {
                f0 = down0[v];
                f1 = down1[v];
            }

            long long base = max(
                f0,
                f1 + w
            );

            long long gain =
                f0 + w - base;

            total += base;

            if (gain > best1) {
                best2 = best1;
                best1 = gain;
                bestFrom = v;
            } else if (gain > best2) {
                best2 = gain;
            }
        }

        // u 作为最初的珠子
        answer = max(answer, total);

        // 把 u 这一侧的信息传给它的儿子
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            int w = weight[e];

            if (v == parent[u]) {
                continue;
            }

            long long childBase = max(
                down0[v],
                down1[v] + w
            );

            // 删除 v 方向的贡献
            long long remain = total - childBase;

            long long bestGain;

            if (bestFrom == v) {
                bestGain = best2;
            } else {
                bestGain = best1;
            }

            up0[v] = remain;

            if (bestGain == NEG) {
                up1[v] = NEG;
            } else {
                up1[v] = remain + bestGain;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        addedge(u, v, w);
        addedge(v, u, w);
    }

    buildTree();
    calcDown();
    reroot();

    cout << answer << '\n';

    return 0;
}