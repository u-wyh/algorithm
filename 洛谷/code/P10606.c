// https://www.luogu.com.cn/problem/P10606
// 题意：小球从数轴 0 点向右出发。经过 i 时可以花 a[i] 让它掉头。每条要求 (x,y) 表示球至少有一次先到 x 再到 y。
// 求满足所有要求的最小总花费。
// 数据范围：1 ≤ n,m ≤ 2 × 10^5，1 ≤ a[i] ≤ 10^8，1 ≤ y<x ≤ n。
// 算法标签：线性扫描

#include<stdio.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    int max=0,a[m+1],b[m+1];
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d",&a[i],&b[i]);
        max=max>a[i]?max:a[i];
    }
    int ans=1e9;
    for(int i=max;i<=n;i++)
    {
        ans=min(ans,nums[i]);
    }
    printf("%d\n",ans);
    return 0;
}
