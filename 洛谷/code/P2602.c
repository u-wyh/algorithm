// https://www.luogu.com.cn/problem/P2602
// 题意：给定正整数 a 和 b，统计闭区间 [a,b] 内所有整数中 0~9 每个数码出现的次数。
// 一行输出 10 个整数。
// 数据范围：1 <= a <= b <= 10^12。
#include <stdio.h>
#include <stdlib.h>
// 算法标签：数位统计、前缀和

long count(long num, int d) {
    long ans = 0;
    for (long right = 1, tmp = num, left, cur; tmp != 0; right *= 10, tmp /= 10) {
        left = tmp / 10;
        if (d == 0) {
            left--;
        }
        ans += left * right;
        cur = tmp % 10;
        if (cur > d) {
            ans += right;
        } else if (cur == d) {
            ans += num % right + 1;
        }
    }
    return ans;
}


long digitsCount(int d, long a, long b) {
    return count(b, d) - count(a - 1, d);
}

int main() {
    long a, b;
    scanf("%ld %ld",&a,&b);
    for (int i = 0; i <= 9; i++) {
        printf("%ld ", digitsCount(i, a, b));
    }
    return 0;
}

