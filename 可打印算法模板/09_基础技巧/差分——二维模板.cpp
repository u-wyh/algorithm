// 用途：多次给闭矩形每格加 1，最后求每格被覆盖的次数。
// 时间：O(n²+m)。
// 空间：O(n²)。
// 注意：本例是 n×n 网格、m 次加值；n、m≤1000，下标从 1 开始。
// 例题：https://www.luogu.com.cn/problem/P3397
// 题意：每块地毯覆盖一个矩形，输出各格子被几块地毯覆盖。
// 思路：四角做差分标记，所有地毯加入后再求二维前缀和。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
int diff[MAXN][MAXN];

// 给左上角 (x1,y1)、右下角 (x2,y2) 的闭矩形加 value。
// 四角分别记 +value、-value、-value、+value，供最后一次性恢复。
void addRectangle(int x1, int y1, int x2, int y2, int value) {
    diff[x1][y1] += value;
    diff[x1][y2 + 1] -= value;
    diff[x2 + 1][y1] -= value;
    diff[x2 + 1][y2 + 1] += value;
}

void restoreGrid(int n) {
    // 按行列递增做二维前缀和，恢复每个格子的实际覆盖数。
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        addRectangle(x1, y1, x2, y2, 1);
    }
    restoreGrid(n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (j > 1) cout << ' ';
            cout << diff[i][j];
        }
        cout << '\n';
    }
    return 0;
}
