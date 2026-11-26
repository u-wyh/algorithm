// https://www.luogu.com.cn/problem/P10452
// 题意：数轴上 n 家商店的坐标为 A[i]。选一个位置建仓库，让仓库到所有商店的距离总和最小。只输出最小总距离。
// 数据范围：1 ≤ n ≤ 10^5，0 ≤ A[i] ≤ 40000。

#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b)
{
    return (*(int *)a-*(int *)b);
}

int main()
{
    int n;
    scanf("%d",&n);
    int a[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    long long ans=0;
    for(int i=1;i<=n;i++)
    {
        ans+=abs(a[i]-a[n/2+1]);
    }
    printf("%lld\n",ans);
    return 0;
}
