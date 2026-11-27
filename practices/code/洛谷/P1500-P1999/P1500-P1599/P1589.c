// https://www.luogu.com.cn/problem/P1589
// 题意：有 n 段泥路和任意多块长度为 L 的木板。
// 可自行安排每块木板的位置，求把所有泥路全部覆盖至少需要多少块。
// 数据范围：n,L ≤ 10000，区间端点满足 s ≤ e ≤ 10^9。
// 算法标签：贪心、排序

#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b;
}road;

int max(int a,int b)
{
    return a>b?a:b;
}

int cmp(const void *a,const void *b)
{
    const road *ra = (const road *)a;
    const road *rb = (const road *)b;

    return (ra->a - rb->a);
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    road nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&nums[i].a,&nums[i].b);
    }
    qsort(nums+1,n,sizeof(road),cmp);
    int ans=0,x=0;
    for(int i=1;i<=n;i++)
    {
        x=max(x,nums[i].a);
        while(x<nums[i].b)
        {
            ans++;
            x+=m;
        }
    }
    printf("%d\n",ans);
    return 0;
}
