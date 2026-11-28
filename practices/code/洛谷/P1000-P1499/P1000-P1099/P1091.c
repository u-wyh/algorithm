// https://www.luogu.com.cn/problem/P1091
// 题意：n 人按原顺序站成一排。
// 让若干人出列，留下的人身高先严格上升再严格下降，最高者可以在两端。
// 求最少需要几人出列。
// 数据范围：2 ≤ n ≤ 100，130 ≤ 身高 ≤ 230。
// 难度评分：1100（洛谷分级换算）
// 算法标签：动态规划

#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    int a[n+1],b[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        a[i]=1;
        b[i]=1;
    }
    for(int i=2;i<=n;i++)
    {
        for(int j=1;j<i;j++)
        {
            if(nums[i]>nums[j])
                a[i]=max(a[j]+1,a[i]);
        }
    }
    for(int i=n-1;i>=1;i--)
    {
        for(int j=n;j>i;j--)
        {
            if(nums[i]>nums[j])
                b[i]=max(b[i],b[j]+1);
        }
    }
    int ans=n;
    for(int i=1;i<=n;i++)
    {
        ans=min(ans,n-a[i]-b[i]+1);
    }
    printf("%d\n",ans);
    return 0;
}
