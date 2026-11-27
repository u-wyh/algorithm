// https://www.luogu.com.cn/problem/P1044
// 题意：数字按 1 到 n 的次序等着入栈。
// 每步可以把下一个数入栈，或把栈顶弹出并放到输出序列末尾。
// 求所有可能的完整输出序列个数。
// 数据范围：1 ≤ n ≤ 18。
// 算法标签：数学

#include<stdio.h>

long long  C(int n)
{
    long long  ans=1;
    for(int i=1;i<=n;i++)
        ans=ans*(2*n-i+1)/i;
    return ans;
}

int main()
{
    int n;
    scanf("%d",&n);
    printf("%lld\n",C(n)/(n+1));
    return 0;
}
