// https://www.luogu.com.cn/problem/P1220
// 题意：直线上有 n 盏路灯（位置单调递增，各有功率 W_i），
// 老张初始在 c 号灯旁。
// 题意：老张以 1 m/s 移动，关灯耗时忽略，初始先关 c 号灯，
// 之后可左右移动关灯。
// 题意：每盏灯在关闭前每秒消耗等同功率的电能，求关完所有灯的最小总耗电。
// 输入：第一行输入 n, c，接下来 n 行每行输入一盏灯的位置和功率 W_i。
// 输出：输出一个整数表示最小总功耗。
// 数据范围：1 <= n <= 50，1 <= c <= n。
// 数据范围：1 <= W_i <= 100，1 <= 路灯位置 <= 100。
// 难度评分：1500（洛谷分级换算）
// 算法标签：区间动态规划、前缀和
#include <stdio.h>
#include <string.h>

#define MAXM 60

int a[MAXM], b[MAXM], sum[MAXM], n, m, c;
int f[MAXM][MAXM][2];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d%d", &n, &c);
    memset(f, 0x7f, sizeof(f)); // 赋成极大值（0x7f7f7f7f在int中为极大值），防止后面的min函数出错
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i], &b[i]);
        sum[i] = sum[i - 1] + b[i];
    }
    f[c][c][0] = f[c][c][1] = 0; // 初始化，瞬间被关

    for (int l = 2; l <= n; l++) {
        for (int i = 1; i + l - 1 <= n; i++) {
            int j = i + l - 1;
            f[i][j][0] = min(f[i + 1][j][0] + (a[i + 1] - a[i]) * (sum[i] + (sum[n] - sum[j])),
                             f[i + 1][j][1] + (a[j] - a[i]) * (sum[i] + (sum[n] - sum[j])));
            f[i][j][1] = min(f[i][j - 1][0] + (a[j] - a[i]) * (sum[i - 1] + (sum[n] - sum[j - 1])),
                             f[i][j - 1][1] + (a[j] - a[j - 1]) * (sum[i - 1] + (sum[n] - sum[j - 1])));
        }
    }

    int ans = min(f[1][n][0], f[1][n][1]);
    printf("%d\n", ans);
    return 0;
}
