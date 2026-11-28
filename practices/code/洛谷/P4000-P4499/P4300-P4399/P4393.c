// https://www.luogu.com.cn/problem/P4393
// 题意：对长度为 n 的序列反复选相邻两数 a_i, a_{i+1} 合
// 并为 max(a_i, a_{i+1}) 并付出该最大值的代价
// 求将序列合并为 1 个元素的最小总代价。
// 数据范围：1 <= n <= 10^6，0 <= a_i <= 10^9。
// 难度评分：1200（洛谷分级换算）
// 算法标签：贪心
#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    long long ans=0;
    scanf("%d",&n);
    int a[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
        if(i!=0)
            ans+=max(a[i],a[i-1]);
    }
    printf("%lld\n",ans);
    return 0;
}
