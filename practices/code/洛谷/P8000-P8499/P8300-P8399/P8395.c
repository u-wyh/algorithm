// https://www.luogu.com.cn/problem/P8395
// 题意：给定正整数 n，
// 求用若干个 4 和 5 相加（不计顺序，仅看 4 和 5 的个数）凑成 n
// 的方案数；不能凑成输出 0。
// 数据范围：100% 数据满足 1 <= n <= 10^6。
// 难度评分：1000（洛谷分级换算）
// 算法标签：数学
#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    if(n/4<n%4)
    {
        printf("0\n");
        return 0;
    }
    printf("%d\n",(n/4-n%4)/5+1);
    return 0;
}
