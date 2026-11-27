// https://www.luogu.com.cn/problem/P9460
// 题意：给定长度为 n 的序列 a。
// 可以进行 k 次修改操作，
// 每次把序列 b（初始为 a）的任意一个元素改为任意整数。
// 序列的众数定义为出现次数最大的所有整数（可多个并列）。
// 求有多少个不同的整数有可能成为修改后序列 b 的众数；
// 若无穷多输出 pigstd。
// 题意：第一行输入 n, k，第二行输入 a_1..a_n；
// 输出一个整数或 pigstd。
// 数据范围：1 <= n <= 10^6，0 <= k <= n，
// 1 <= a_i <= n。
// 算法标签：二分答案、计数统计
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM 1000005

int a[MAX_NUM], vis[MAX_NUM];
int n, k, maxa = 0; // maxa 为原数组中众数出现的次数
int mp[MAX_NUM];    // 用来存每个数出现的次数

int check(int x) {
    memset(vis, 0, sizeof(vis));
    x += k;
    long long m = 0;
    for (int i = 1; i <= n; i++) {
        if (mp[a[i]] > x && vis[a[i]] == 0) {
            vis[a[i]] = 1;
            m += mp[a[i]] - x;
        }
    }
    if (m > k) return 0;
    else return 1;
}

int main() {
    int ans = 0;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        mp[a[i]]++;
        maxa = (mp[a[i]] > maxa) ? mp[a[i]] : maxa;
    }
    if (k >= maxa) { // 并无意义，只是为了方便
        printf("pigstd\n");
        return 0;
    }
    int l = 0, r = 1000000, mid;
    while (l < r) { // 二分
        mid = (l + r) >> 1;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    if (l == 0) {
        printf("pigstd\n");
        return 0;
    }
    for (int i = 1; i <= 1000000; i++) {
        if (mp[i] >= l) ans++;
    }
    printf("%d\n", ans);
    return 0;
}
