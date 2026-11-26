// https://www.luogu.com.cn/problem/P1223
// 题意：n 个人共用一个水龙头，每人的接水时长为 t[i]。
// 找一种顺序让平均等待时间最短，等待时间不计本人接水。
// 时长相同按编号升序。
// 输出顺序和保留两位小数的平均等待时间。
// 数据范围：1 ≤ n ≤ 1000，1 ≤ t[i] ≤ 10^6，时长可以相同。

#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b;
}time;

int cmp(void *a,void *b)
{
    time *ta=(time *)a;
    time *tb=(time *)b;
    return ta->b - tb->b;
}

int main()
{
    int n;
    scanf("%d",&n);
    time t[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&t[i].b);
        t[i].a=i;
    }
    qsort(t+1,n,sizeof(time),cmp);
    long long ans=0;
    printf("%d ",t[1].a);
    for(int i=2;i<=n;i++)
    {
        printf("%d ",t[i].a);
        ans+=t[i-1].b*(n-i+1);
    }
    //ans-=t[n].b;
    printf("\n");
    double ans1=ans*1.0/n;
    printf("%.2lf\n",ans1);
    return 0;
}
