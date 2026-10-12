// 用途：对每个查询点，找覆盖它的最短闭区间长度。
// 时间：O((n+m) log(n+m))。
// 空间：O(n+m)。
// 注意：n、m 均不超过 200000；区间和查询坐标可为任意 int 值。
// 例题：https://leetcode.cn/problems/minimum-interval-to-include-each-query/
// 题意：每个查询点求覆盖它的最短给定区间长度。
// 思路：按坐标扫描，优先队列保留当前覆盖查询点的区间，队首最短。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

struct Interval {
    int l, r;
};
struct Query {
    int x, id;
};

Interval seg[MAXN];
Query ask[MAXN];
long long answer[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> seg[i].l >> seg[i].r;
    for (int i = 1; i <= m; ++i) {
        cin >> ask[i].x;
        ask[i].id = i;
    }
    sort(seg + 1, seg + n + 1, [](const Interval &a, const Interval &b) {
        return a.l < b.l;
    });
    sort(ask + 1, ask + m + 1, [](const Query &a, const Query &b) {
        return a.x < b.x;
    });

    // 堆中按区间长度排序；过期区间在堆顶时再弹出。
    priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                   greater<pair<long long, int>>> heap;
    for (int i = 1, j = 1; i <= m; ++i) {
        const int x = ask[i].x;
        while (j <= n && seg[j].l <= x) {
            heap.push({1LL * seg[j].r - seg[j].l + 1, seg[j].r});
            ++j;
        }
        while (!heap.empty() && heap.top().second < x) heap.pop();
        answer[ask[i].id] = heap.empty() ? -1 : heap.top().first;
    }
    for (int i = 1; i <= m; ++i) cout << answer[i] << '\n';
    return 0;
}
