// https://www.luogu.com.cn/problem/P8161
// 题意：共 M 周、有 N 门课（1..N），每周有 N 个课时，第 i 个课时上课程 i。
// 在总共 N * M 个课时中的每一节，可选择：1) 上课，使课程 i 的理解度增加 A_i；
// 2) 不上该课而任选一门课程 j 自学，使课程 j 的理解度增加 B_j。
// 初始所有课程理解度均为 0，非上课时间不学习。
// 求期末时 N 门课理解度的最小值的最大可能值。
// 第一行输入 N, M，第二行 N 个整数 A_1..A_N，第三行 N 个整数 B_1..B_N。
// 输出一行一个整数。
// 数据范围：1 <= N <= 3*10^5，1 <= M <= 10^9，1 <= A_i, B_i <= 10^9。
// 算法标签：二分答案、贪心
#include <stdio.h>
#include <stdlib.h>

#define N 300007

int n;
long long m;
long long a[N], b[N];

int check(long long lim) {
    long long s = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i] * m >= lim) {
            s += (a[i] * m - lim) / a[i]; // 多余的
        } else {
            // 注意这里要加上b[i]-1来确保向上取整
            s -= (lim - a[i] * m + b[i] - 1) / b[i]; // 缺少的
        }
    }
    return s >= 0;
}

int main() {
    scanf("%d %lld", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
    }
    int mx = 0;
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &b[i]);
        a[i] = (a[i] > b[i]) ? a[i] : b[i]; // 使用三元运算符简化
        mx = (a[i] > mx) ? a[i] : mx; // 更新最大值
    }
    long long l = 0, r = (long long)mx * m;
    while (l <= r) {
        long long mid = l + (r - l) / 2;
        if (check(mid)) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    printf("%lld\n", l - 1); // 因为循环结束时l已经超出了答案，所以要减1
    return 0;
}
