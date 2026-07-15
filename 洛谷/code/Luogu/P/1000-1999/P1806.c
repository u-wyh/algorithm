/*
    这段代码的思路可以说是真牛逼
    ans[j]从大到小填数字    ans[j] += ans[j - i];
    什么意思呢？   最后一把跑i圈    总共跑了j圈
    ans[j-i]的每一圈都不会超过i  为什么呢   因为i从1开始增加
*/
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
