// https://www.luogu.com.cn/problem/P1413
// 题意：棋盘有 6 行 60 列，每个僵尸在指定时刻从指定行的第 60 列出现，
// 以每秒一格向左走。
// 一个坚果能立即消灭某一行当时在场的所有僵尸，必须在它们越过第 1 列前消灭。
// 求最少坚果数。
// 数据范围：n ≤ 2000，1 ≤ P ≤ 6，t ≤ 100000，
// 允许同一时刻同一行出现多个僵尸。
// 难度评分：900（洛谷分级换算）
// 算法标签：贪心、排序

#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b;
}zombie;

int max(int a,int b)
{
    return a>b?a:b;
}

int cmp(const void *a,const void *b)
{
    zombie *za=(zombie *)a;
    zombie *zb=(zombie *)b;
    if(za->a>zb->a)
        return 1;
    if(za->a<zb->a)
        return -1;
    return za->b-zb->b;
}
int main()
{
    int n;
    scanf("%d",&n);
    zombie nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&nums[i].a,&nums[i].b);
    }
    qsort(nums+1,n,sizeof(zombie),cmp);
    /*for(int i=1;i<=n;i++)
    {
        printf("%d %d\n",nums[i].a,nums[i].b);
    }*/
    int ans=1;
    int x=nums[1].b+59;
    for(int i=2;i<=n;i++)
    {
        if(nums[i].a==nums[i-1].a)
        {
            if(nums[i].b>x)
            {
                ans++;
                x=nums[i].b+59;
            }
        }
        else
        {
            ans++;
            x=nums[i].b+59;
        }
    }
    printf("%d\n",ans);
    return 0;
}
