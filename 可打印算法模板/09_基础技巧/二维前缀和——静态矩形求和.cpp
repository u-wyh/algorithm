// 用途：矩阵不修改时，快速求任意闭矩形内的元素和。
// 时间：建表 O(nm)，每次查询 O(1)；总计 O(nm+q)。
// 空间：O(nm)。
// 注意：1 下标，prefix 的第 0 行/列为 0；n、m≤1000，求和用 long long。
// 输入：n m q、n×m 个数、q 组 x1 y1 x2 y2；每组输出一个矩形和。
#include <bits/stdc++.h>
using namespace std;

const int MAXR = 1005, MAXC = 1005;
long long prefix[MAXR][MAXC];

long long rectangleSum(int x1, int y1, int x2, int y2) {
    // 大矩形减去上方和左方，再补回被减了两次的左上角。
    return prefix[x2][y2] - prefix[x1 - 1][y2]
           - prefix[x2][y1 - 1] + prefix[x1 - 1][y1 - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    if (!(cin >> n >> m >> q)) return 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            long long value;
            cin >> value;
            // prefix[i][j] 表示左上角 (1,1) 到 (i,j) 的总和。
            prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1]
                           - prefix[i - 1][j - 1] + value;
        }
    }
    while (q--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << rectangleSum(x1, y1, x2, y2) << '\n';
    }
    return 0;
}
