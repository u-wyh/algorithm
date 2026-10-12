// 用途：在 n×n 带权二分图中，给每个左点匹配不同右点，使边权总和最大。
// 时间：O(n³)。
// 空间：O(n²)。
// 注意：输入完整权值矩阵，可含负权；n≤200，|边权|≤10^9。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;
const long long INF = LLONG_MAX / 4;
int n, matchRight[MAXN];
long long weight[MAXN][MAXN], labelLeft[MAXN], labelRight[MAXN], slack[MAXN];
bool seenLeft[MAXN], seenRight[MAXN];

bool augment(int u) {
    seenLeft[u] = true;
    for (int v = 0; v < n; ++v) {
        if (seenRight[v]) continue;
        long long gap = labelLeft[u] + labelRight[v] - weight[u][v];
        if (gap == 0) {
            seenRight[v] = true;
            if (matchRight[v] == -1 || augment(matchRight[v])) {
                matchRight[v] = u;
                return true;
            }
        } else {
            slack[v] = min(slack[v], gap);
        }
    }
    return false;
}

long long maximumMatching() {
    fill(matchRight, matchRight + n, -1);
    for (int u = 0; u < n; ++u) {
        labelLeft[u] = weight[u][0];
        for (int v = 1; v < n; ++v)
            labelLeft[u] = max(labelLeft[u], weight[u][v]);
    }
    for (int u = 0; u < n; ++u) {
        fill(slack, slack + n, INF);
        while (true) {
            fill(seenLeft, seenLeft + n, false);
            fill(seenRight, seenRight + n, false);
            if (augment(u)) break;
            long long step = INF;
            for (int v = 0; v < n; ++v)
                if (!seenRight[v]) step = min(step, slack[v]);
            for (int x = 0; x < n; ++x)
                if (seenLeft[x]) labelLeft[x] -= step;
            for (int v = 0; v < n; ++v) {
                if (seenRight[v]) labelRight[v] += step;
                else slack[v] -= step;
            }
        }
    }
    long long answer = 0;
    for (int v = 0; v < n; ++v) answer += weight[matchRight[v]][v];
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int u = 0; u < n; ++u)
        for (int v = 0; v < n; ++v) cin >> weight[u][v];
    cout << maximumMatching() << '\n';
    return 0;
}
