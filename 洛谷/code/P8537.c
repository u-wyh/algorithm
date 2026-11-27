// https://www.luogu.com.cn/problem/P8537
// 题意：给定长为 n 的序列 a 和目标序列 b，每次操作可以翻转整个序列 a，或将序列中某个数加上任意整数。求将 a 变为 b 所需的最少操作次数。
// 数据范围：100% 数据满足 1 <= n <= 5*10^5，1 <= a_i, b_i <= 10^9。
// 算法标签：贪心、枚举
#include<stdio.h>
#include<math.h>

int main()
{
    int n;
    scanf("%d",&n);
    int a1[n+1],a2[n+1],b[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a1[i]);
        a2[n-i+1]=a1[i];
    }
    int ans1=0,ans2=1;
    for(int i=1;i<=n;i++){
        scanf("%d",&b[i]);
        ans1+=(a1[i]!=b[i])?1:0;
        ans2+=(a2[i]!=b[i])?1:0;
    }
    printf("%d\n",ans1<ans2?ans1:ans2);
    return 0;
}
