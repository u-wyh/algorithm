// https://www.luogu.com.cn/problem/P1842
// 题意：把 N 头牛摞起来。第 i 头牛的压扁指数是它上方所有牛的总重量减去它的力量 S_i。安排顺序，让所有牛中的最大压扁指数尽量小。
// 数据范围：1 ≤ N ≤ 5×10^4，1 ≤ W_i ≤ 10^4，1 ≤ S_i ≤ 10^9。
// 算法标签：贪心、排序

#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    long long  w,s;
}row;

long long  max(long long a,long long  b)
{
    return a>b?a:b;
}

int cmp(const void *a,const void *b)
{
    row * ra=(row *)a;
    row * rb=(row *)b;

    return ((ra->w+ra->s)-(rb->w+rb->s));
}

int main()
{
    int n;
    scanf("%d",&n);
    row nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%lld %lld",&nums[i].w,&nums[i].s);
    }
    qsort(nums+1,n,sizeof(row),cmp);
    long long  sum=nums[1].w,ans=-1*nums[1].s;
    for(int i=2;i<=n;i++)
    {
        ans=max(ans,sum-nums[i].s);
        sum+=nums[i].w;
    }
    printf("%lld\n",ans);
    return 0;
}
