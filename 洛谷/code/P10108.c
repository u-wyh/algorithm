#include <stdio.h>
#include <stdlib.h>

#define MAX_N 101
#define MAX_F 20001 // 由于 f 数组需要计算到 N+max{ai}，这里假定最大值足够大

int a[MAX_N], b[MAX_F], f[MAX_F];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }

    // 初始化 f 数组为负无穷大
    for (int i = 0; i < MAX_F; i++) {
        f[i] = -1e9;
    }

    f[0] = 0; // f[0] 初始化为 0

    // 动态规划填表
    for (int j = 0; j < 2 * n; j++) { // 考虑到可能需要计算到 2N
        for (int i = 0; i < m; i++) {
            if (j >= a[i]) {
                // 注意：这里 b[j-a[i]] 可能越界，因为 b 数组只有 n 个元素
                // 假设题目保证 a[i] 不会使 j-a[i] 越界
                f[j] = (f[j] > f[j - a[i]] + (j - a[i] < n ? b[j - a[i]] : 0)) ? f[j] : f[j - a[i]] + (j - a[i] < n ? b[j - a[i]] : 0);
            }
        }
    }

    int ans = -1e9; // 初始化答案变量为负无穷大
    for (int i = n; i < 2 * n; i++) {
        if (f[i] > ans) {
            ans = f[i];
        }
    }

    printf("%d\n", ans);

    return 0;
}
