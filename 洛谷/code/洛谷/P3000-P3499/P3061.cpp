// https://www.luogu.com.cn/problem/P3061
// 题意：给定 N 条二维线段构成的围栏和 C 头牛的坐标。
// 线段仅在端点相交，且每条线段两端各接触另外两条线段。
// 牛的坐标互不相同且不在任何围栏上。
// 两头牛不碰围栏能互相到达即属同一社区，求最大社区的牛数。
// 输入：第一行输入 N 和 C，
// 后 N 行输入围栏端点 x1, y1, x2, y2，
// 再 C 行输入牛坐标 x, y。
// 输出：输出最大社区包含的牛的数量。
// 数据范围：1 <= N, C <= 1000，
// 坐标为 [0, 10^6] 内的整数。
// 原题：https://usaco.org/index.php?cpid=208&page=viewproblem2
// 算法标签：计算几何、并查集、射线法
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
int fa[MAXN];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void unite(int a, int b) {
    a = find(a); b = find(b);
    if (a != b) fa[a] = b;
}

struct Fence {
    int x1, y1, x2, y2;
} f[MAXN];

// 判断两条栅栏是否有公共端点
bool connected(const Fence& a, const Fence& b) {
    return (a.x1 == b.x1 && a.y1 == b.y1) ||
           (a.x1 == b.x2 && a.y1 == b.y2) ||
           (a.x2 == b.x1 && a.y2 == b.y1) ||
           (a.x2 == b.x2 && a.y2 == b.y2);
}

// 水平向右射线 (cx, cy) 是否穿过栅栏 f
bool crosses(int cx, int cy, const Fence& f) {
    // 必须跨越水平线 y = cy（半开半闭，避免顶点重复计算）
    bool up1 = f.y1 > cy;
    bool up2 = f.y2 > cy;
    if (up1 == up2) return false;  // 两个端点在同一侧，不相交

    // 计算交点的 x 坐标（用交叉相乘避免浮点误差）
    long long dx = f.x2 - f.x1;
    long long dy = f.y2 - f.y1;
    long long numerator = (long long)(cy - f.y1) * dx;
    // 交点 x = f.x1 + numerator / dy
    // 因为 dy 可能为负，统一转为正数比较
    if (dy < 0) {
        dx = -dx;
        dy = -dy;
        numerator = -numerator;
    }
    // 交点 x > cx  等价于  f.x1 * dy + numerator > cx * dy
    long long lhs = (long long)f.x1 * dy + numerator;
    long long rhs = (long long)cx * dy;
    return lhs > rhs;
}

int main() {
    int N, C;
    cin >> N >> C;
    for (int i = 0; i < N; i++) {
        cin >> f[i].x1 >> f[i].y1 >> f[i].x2 >> f[i].y2;
        fa[i] = i;
    }
    // 1. 合并相连的栅栏，每个连通块就是一个封闭区域
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            if (connected(f[i], f[j])) unite(i, j);

    // 2. 为每个连通块分配区域编号
    unordered_map<int, int> region_id;
    int reg_cnt = 0;
    for (int i = 0; i < N; i++) {
        int root = find(i);
        if (!region_id.count(root)) region_id[root] = reg_cnt++;
    }

    // 3. 对每头奶牛，统计它所在区域集合
    map<vector<int>, int> community;
    int ans = 0;
    for (int k = 0; k < C; k++) {
        int cx, cy;
        cin >> cx >> cy;
        vector<int> parity(reg_cnt, 0);  // 每个区域被穿过的次数奇偶性

        for (int i = 0; i < N; i++) {
            if (!crosses(cx, cy, f[i])) continue;
            int reg = region_id[find(i)];
            parity[reg] ^= 1;  // 奇偶性翻转
        }

        vector<int> inside;
        for (int r = 0; r < reg_cnt; r++)
            if (parity[r]) inside.push_back(r);

        sort(inside.begin(), inside.end());
        community[inside]++;
        ans = max(ans, community[inside]);
    }

    cout << ans << endl;
    return 0;
}