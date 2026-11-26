// https://www.luogu.com.cn/problem/P2878
// 题意：n 头牛在吃花，第 i 头距牛圈 T_i 分钟、每分钟吃 D_i 朵花。
// 每次只能赶一头回牛圈（往返耗时 2*T_i 分钟），求所有牛吃掉花的最小总朵数。
// 输出最小总朵数。
// 数据范围：1 <= n <= 10^5，1 <= T_i <= 2*10^6，1 <= D_i <= 100。
#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int t,d;
}row;

int cmp(const void *a,const void *b)
{
    row * ra=(row *)a;
    row * rb=(row *)b;

    return -(ra->d * rb->t)+(ra->t * rb->d);
}

int main()
{
    int n;
    scanf("%d",&n);
    row nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&nums[i].t,&nums[i].d);
    }
    qsort(nums+1,n,sizeof(row),cmp);
/*
    printf("----------------------------\n");
    for(int i=1;i<=n;i++)
    {
        printf("%d %d\n",nums[i].t,nums[i].d);
    }
    printf("----------------------------\n");
*/
    int T=0;
    long long ans=0;
    for(int i=1;i<=n;i++)
    {
        ans+=(T*nums[i].d);
        T=(T+nums[i].t*2);
        //printf("%d %d\n",T,ans);
    }
    printf("%lld\n",ans);
    /*
    long long sum[n+1];
    sum[0]=0;
    for (int i=1;i<=n;++i)
        sum[i]=sum[i-1]+nums[i].d;
    long long ans=0;
    for (int i=1;i<=n;++i)
        ans+=2*nums[i].t*(sum[n]-sum[i]);

    printf("%lld\n",ans);
    */
    return 0;
}
