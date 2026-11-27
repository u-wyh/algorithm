// https://www.luogu.com.cn/problem/P9228
// 题意：有 n 次火元素攻击（伤害 a_1..a_n）和 m 次冰元素攻击（伤害 b_1..b_m），任意安排这 n+m 次攻击的顺序。
// 初始无元素附着：攻击无附着目标会附着自身元素；
// 火攻命中冰附着目标时本次伤害 * 2 并清空附着；
// 冰攻命中火附着目标时本次伤害 + k 并清空附着。
// 题意：第一行输入 n, m, k，第二行输入 a_1..a_n，第三行输入 b_1..b_m；输出一行一个整数表示最大总伤害。
// 数据范围：1 <= n, m <= 10^6，0 <= a_i, b_i, k <= 10^9。
// 算法标签：贪心、排序
#include <stdio.h>
#include <stdlib.h>

#define int long long
#define N 1000000 + 100000

// 比较函数，用于qsort
int compare(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (y - x); // 注意这里返回y-x以实现降序排序
}

int main() {
    int n, m, k;
    scanf("%lld %lld %lld", &n, &m, &k);
    int a[N], b[N];
    int ans = 0, kk = 0;

    // 读取数组a并求和
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
        ans += a[i];
    }

    // 读取数组b并求和
    for (int i = 0; i < m; i++) {
        scanf("%lld", &b[i]);
        ans += b[i];
    }

    // 对数组a进行排序（降序）
    qsort(a, n, sizeof(int), compare);

    // 找出满足条件的元素数量并更新ans
    int minn = (n < m) ? n : m;
    for (int i = 0; i < minn; i++) {
        if (a[i] > k) {
            ans += a[i];
            kk++;
        }
    }

    // 剩下的元素都按k计算
    ans += k * (minn - kk);

    // 输出结果
    printf("%lld\n", ans);

    // main函数应返回int类型，并且通常返回0表示成功
    return 0;
}
