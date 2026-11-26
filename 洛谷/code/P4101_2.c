// https://www.luogu.com.cn/problem/P4101
// 题意：第一行输入数据组数 T，接下来 T 行每行输入两个正整数 n 和 m。
// 初始有 n 堆各 1 个石子，双方轮流操作，每次合并任意两堆石子但合并后石子数不能超过 m，不能操作者输。
// 输出 T 行，先手胜输出 0，后手胜输出 1。
// 数据范围：1 <= T <= 100，1 <= n, m <= 10^9。
#include<stdio.h>

int T;
long long int n, m;

int main() {
    scanf("%d", &T);
    for(int i = 1; i <= T; i++) {
        scanf("%lld%lld", &n, &m);
        long long int ans = (n / m) * (m - 1) + ((n % m) ? (n % m - 1) : 0);
        if(ans & 1) {
            printf("0\n");
        } else {
            printf("1\n");
        }
    }
    return 0;
}
