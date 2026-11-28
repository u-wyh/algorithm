// https://www.luogu.com.cn/problem/P2813
// 题意：敌方有 M 个防御系统（防御力），己方有 N 个攻击系统（攻击力）。
// 攻击力严格大于防御力可破坏该防御系统；全破坏后剩余攻击全部打在敌方本体。
// 求对敌方本体造成的最大伤害。
// 数据范围：1 <= N, M <= 10^5。
// 难度评分：900（洛谷分级换算）
// 算法标签：贪心、排序、双指针
#include<stdio.h>

int cmp(const void *a,const void *b)
{
    return (*(int *)a-*(int *)b);
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+1],b[m+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&b[i]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    qsort(b+1,m,sizeof(int),cmp);
    int t=1;
    for(int i=1;i<=m;i++)
    {
        while(a[t]==0)
            t++;
        if(a[t]<b[i])
        {
            t++;
            b[i]=0;
        }
    }
    long long ans=0;
    if(t<=n)
        printf("0\n");
    else
    {
        for(int i=1;i<=m;i++)
            ans+=b[i];
        printf("%lld\n",ans);
    }
    return 0;
}
