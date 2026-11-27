// https://www.luogu.com.cn/problem/P1665
// 题意：给平面上 N 个不同的点，统计有多少组四个点恰好构成正方形。
// 正方形可以倾斜，不要求边平行于坐标轴。
// 数据范围：1 ≤ N ≤ 500，横纵坐标在 [-50,50]，点不重合。
// 算法标签：枚举、计算几何

#include <stdio.h>

int n, ans;
int x[60000], y[60000], vis[1100][1100];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &x[i], &y[i]);
        x[i] = (x[i] + 51) << 1;
        y[i] = (y[i] + 51) << 1;
        vis[x[i]][y[i]] = 1;
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int midx = (x[i] + x[j]) / 2;
            int midy = (y[i] + y[j]) / 2;

            int x1 = midx - (midy - y[i]), y1 = midy + (midx - x[i]);
            int x2 = midx + (midy - y[i]), y2 = midy - (midx - x[i]);

            if (x1 <= 0) continue;
            if (x2 <= 0) continue;
            if (y1 <= 0) continue;
            if (y2 <= 0) continue;
            if (vis[x1][y1] && vis[x2][y2]) ++ans;
        }
    }
    printf("%d\n", ans >> 1);
    return 0;
}
