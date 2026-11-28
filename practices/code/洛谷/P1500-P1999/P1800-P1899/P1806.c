// https://www.luogu.com.cn/problem/P1806
// 题意：把 n 圈分成至少两次跑完，每次跑正整数圈，且每次都比上一次多。
// 求不同的圈数分配方案有多少种。
// 数据范围：5 ≤ n ≤ 500。

/*
    这段代码的思路可以说是真牛逼
    ans[j]从大到小填数字    ans[j] += ans[j - i];
    什么意思呢？   最后一把跑i圈    总共跑了j圈
    ans[j-i]的每一圈都不会超过i  为什么呢   因为i从1开始增加
*/
// 难度评分：1300（洛谷分级换算）
// 算法标签：0-1背包、动态规划
#include <stdio.h>

long long n, ans[501];

int main() {
    scanf("%lld", &n);
    ans[0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = n; j >= i; j--) {
            ans[j] += ans[j - i];
        }
    }
    //printf("%lld\n", ans[n]-1);
    for(int i=1;i<=n;i++)
        printf("%10d",ans[i]-1);

    return 0;
}
