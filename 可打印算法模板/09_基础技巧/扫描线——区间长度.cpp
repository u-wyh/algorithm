// 用途：对每个查询点 x，找满足 l≤x≤r 的最短闭区间长度 r-l+1。
// 时间：O((n+m) log(n+m))。
// 空间：O(n+m)。
// 注意：n、m 均不超过 200000；区间和查询坐标可为任意 int 值。
// 例题：https://leetcode.cn/problems/minimum-interval-to-include-each-query/
// 题意：给定 n 个区间和 m 个查询点；逐点输出最短覆盖区间长度，无覆盖输出 -1。
// 思路：查询点从左到右扫；加入左端点已到达的区间，堆顶始终取最短且未过期的区间。
// 例：[1,4]、[2,2] 对点 2、3 的答案分别是 1、4。
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

    int n, m; // n 个闭区间，m 个查询点。
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> seg[i].l >> seg[i].r;
    for (int i = 1; i <= m; ++i) {
        cin >> ask[i].x;
        ask[i].id = i;
    }
    // 区间按左端点排序，查询按坐标排序，才能用一个指针逐步加入区间。
    sort(seg + 1, seg + n + 1, [](const Interval &a, const Interval &b) {
        return a.l < b.l;
    });
    sort(ask + 1, ask + m + 1, [](const Query &a, const Query &b) {
        return a.x < b.x;
    });

    // 堆元素 = {区间长度, 右端点}；最短区间在堆顶。
    // 过期区间即使暂时压在堆底，也不会成为答案，等到堆顶再删除即可。
    priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                   greater<pair<long long, int>>> heap;
    for (int i = 1, j = 1; i <= m; ++i) { // j 指向尚未加入堆的第一个区间。
        const int x = ask[i].x;
        // 左端点 ≤ x 的区间从此刻起可能覆盖 x，全部加入候选集合。
        while (j <= n && seg[j].l <= x) {
            heap.push({1LL * seg[j].r - seg[j].l + 1, seg[j].r});
            ++j;
        }
        // 右端点 < x 的堆顶已经过期；反复弹出，直到堆顶真正覆盖 x。
        while (!heap.empty() && heap.top().second < x) heap.pop();
        // 排序打乱了询问顺序，按原编号保存，最后按输入顺序输出。
        answer[ask[i].id] = heap.empty() ? -1 : heap.top().first;
    }
    for (int i = 1; i <= m; ++i) cout << answer[i] << '\n';
    return 0;
}
