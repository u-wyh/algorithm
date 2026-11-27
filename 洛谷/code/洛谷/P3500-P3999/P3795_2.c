// https://www.luogu.com.cn/problem/P3795
// 题意：输入一个正整数 k（输入格式中记为 x）。
// 设集合 N = M = {1, 2, ..., k}，
// 求满足 f(f(x)) = x 的 N 到 M 的不同映射 f 的个数。
// 输出答案对 14233333 取余的结果。
// 数据范围：1 <= k <= 10^7；注意本题内存限制为 20MB。
// 算法标签：递推、组合数学
#include<stdio.h>
#define mod 14233333
int main()
{
    int n;
    scanf("%d",&n);
    long long a=1;
    long long b=1;
    long long c;
    for(int i=2;i<=n;i++)
    {
        c=(b+a*(i-1)%mod)%mod;
        a=b;
        b=c;
    }
    printf("%lld\n",c);
    return 0;
}
