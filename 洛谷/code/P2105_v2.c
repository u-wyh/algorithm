#include <stdio.h>
#include <string.h>

#define MAXN 501
#define MAXK 20001

int x[MAXN], y[MAXN], n, m, k;
int flag[MAXK], vis[MAXK], sum, ans;

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= k; i++) {
        scanf("%d %d", &x[i], &y[i]);
        vis[x[i]] = 1; // 标记有国王的行
    }

    memset(flag, 0, sizeof(flag)); // 初始化flag数组
    ans = 0;

    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue; // 如果当前行有国王，则跳过

        sum = m; // 初始化当前行的空闲列数为m

        for (int j = 1; j <= k; j++) {
            if (flag[y[j]] != i) sum--; // 减去当前国王控制的列
            flag[y[j]] = i; // 标记列被当前行国王控制

            if (x[j] < i) { // 当前国王在当前行上方
                if (y[j] + i - x[j] >= 1 && y[j] + i - x[j] <= m) {
                    // 右下方向对角线
                    if (flag[y[j] + i - x[j]] != i) sum--;
                    flag[y[j] + i - x[j]] = i;
                }
                if (y[j] - i + x[j] >= 1 && y[j] - i + x[j] <= m) {
                    // 左下方向对角线
                    if (flag[y[j] - i + x[j]] != i) sum--;
                    flag[y[j] - i + x[j]] = i;
                }
            } else { // 当前国王在当前行下方
                if (y[j] + (x[j] - i) >= 1 && y[j] + (x[j] - i) <= m) {
                    // 右下方向对角线
                    if (flag[y[j] + (x[j] - i)] != i) sum--;
                    flag[y[j] + (x[j] - i)] = i;
                }
                if (y[j] - (x[j] - i) >= 1 && y[j] - (x[j] - i) <= m) {
                    // 左下方向对角线
                    if (flag[y[j] - (x[j] - i)] != i) sum--;
                    flag[y[j] - (x[j] - i)] = i;
                }
            }
        }

        ans += sum; // 累加当前行的空闲列数
    }

    printf("%d\n", ans);
    return 0;
}
