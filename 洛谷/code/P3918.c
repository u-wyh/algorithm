// https://www.luogu.com.cn/problem/P3918
// 题意：飞行共 n 个单位时间，每单位时间可选择 k 种特技动作之一，第 i 种刺激程度为 c_i。
// 若第一次做某动作则本次得 0 分，否则得（距上次做该动作的时间差）* c_i 分。求 n 个单位时间能获得的最大总价值。
// 数据范围：1 <= n <= 10^3，1 <= k <= 300，0 <= c_i <= 10^3。
#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b)
{
    return (*(int *)b-*(int *)a);
}

int main()
{
    int k,n;
    scanf("%d %d",&k,&n);
    int a[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    long long ans=0;
    for(int i=1;i<=n;i++)
    {
        if(k-2*i+1>=0)
            ans+=(a[i]*(k-2*i+1));
        else
            break;
    }
    printf("%lld\n",ans);
    return 0;
}
