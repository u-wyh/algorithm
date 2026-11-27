// https://www.luogu.com.cn/problem/P1130
// 题意：申请有 N 个步骤、M 个小组。
// 给出每组做每步所需天数。
// 第一步任选组，之后每一步可以留在当前组，或换到下一组，
// 第 M 组的下一组是第 1 组。
// 求做完所有步骤的最少耗时。
// 数据范围：1 ≤ N,M ≤ 2000，每项耗时在 [0,100000]。
// 算法标签：动态规划

#include <stdio.h>
#include <limits.h> // 用于INT_MAX
#include <string.h> // 用于memset，但在这个例子中其实不需要

int n, m;
int a[2005][2005];
int ans = INT_MAX; // ans必须要定大，不然找不到最小值

int min(int a, int b);

int main() {
    scanf("%d%d", &n, &m);
    // 注意：在C语言中，数组索引通常从0开始，所以这里直接从0开始读取
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // 从倒数第2步开始，向第一步推进
    // 注意这里的边界条件，因为j是从n-2开始的，所以j+1不会越界
    for (int j = n - 2; j >= 0; j--) {
        for (int i = 0; i < m; i++) {
            // 取最小值，更新为之后的步骤的最小值
            // 注意使用模运算来处理环形队列的情况
            a[i][j] = min(a[(i + 1) % m][j + 1], a[i][j + 1]) + a[i][j];
        }
    }

    // 找答案
    for (int i = 0; i < m; i++) {
        ans = min(ans, a[i][0]);
    }

    // 输出答案
    printf("%d\n", ans);

    return 0;
}

// 添加min函数定义，因为C标准库中没有min函数
int min(int a, int b) {
    return a < b ? a : b;
}
