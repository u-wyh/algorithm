// https://www.luogu.com.cn/problem/P8784
// 题意：输入整数 N，用大小 2 的 I 型（1*2）和大小 3 的 L 型（3 格拐角）积木（可任意旋转）无缝铺满方向固定的 2*N 矩形画布
// 输出铺法总数对 10^9+7 取模的结果。
// 数据范围：1 <= N <= 10^7。
#include <stdio.h>
#include <stdlib.h> // 引入stdlib.h以使用malloc和free

const int mod = 1e9 + 7;
const int N = 1e7;

int main() {
    int *f = (int*)malloc(N * sizeof(int)); // 动态分配内存
    if (f == NULL) { // 检查内存是否成功分配
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // 初始化数组的前几个元素
    f[0] = 0;
    f[1] = 1;
    f[2] = 2;
    f[3] = 5;

    int n;
    scanf("%d", &n);

    // 计算f[n]
    for (int i = 4; i <= n; ++i) {
        f[i] = (2 * f[i - 1] % mod + f[i - 3] % mod) % mod;
    }

    printf("%d\n", f[n]);

    // 释放内存
    free(f);

    return 0;
}
