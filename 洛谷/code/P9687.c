// https://www.luogu.com.cn/problem/P9687
// 题意：多组数据（共 T 组）。
// 构造长度为 n 的 01 字符串（0 为白，1 为黑）
// 要求其中恰好有 p 个位于下标 [2, n-1] 的 '0' 满足其左右两个相邻字符均为 '1'（即形如 "101" 中间的 '0' 的个数恰好为 p）。
// 若有解输出字典序最小的方案，无解输出 -1。
// 题意：第一行输入 T，每组一行输入 n, p；每组输出长度为 n 的 01 串或 -1。
// 数据范围：1 <= T <= 100，1 <= n, p <= 10^5。
#include<stdio.h>

int main()
{
    int t;
    scanf("%d",&t);
    for(int k=1;k<=t;k++)
    {
        int n,p;
        scanf("%d %d",&n,&p);
        if(n<2*p+1)
        {
            printf("-1\n");
        }
        else
        {
            int nums[n+1];
            for(int i=1;i<=n;i++)
            {
                nums[i]=0;
            }
            int j=n;
            for(int i=0;i<=p;i++)
            {
                nums[j]=1;
                j-=2;
            }
            for(int i=1;i<=n;i++)
            {
                printf("%d",nums[i]);
            }
            printf("\n");
        }
    }
    return 0;
}
