// https://www.luogu.com.cn/problem/P1803
// 题意：给定 n 场比赛的开始和结束时间，参加一场就必须完整参加，
// 不能同时参加两场。求最多能参加多少场，前一场结束时可以接下一场。
// 数据范围：1 ≤ n ≤ 10^6，0 ≤ a_i < b_i ≤ 10^6。
// 难度评分：900（洛谷分级换算）
// 算法标签：贪心、排序

#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b;
}time;

int cmp(const void *a,const void *b)
{
    time * ta=(time *)a;
    time * tb=(time *)b;
    return ta->b-tb->b;
}

int main()
{
    int n;
    scanf("%d",&n);
    time nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&nums[i].a,&nums[i].b);
    }
    qsort(nums+1,n,sizeof(time),cmp);
    int count=1,last=nums[1].b;
    for(int i=2;i<=n;i++)
    {
        if(nums[i].a>=last)
        {
            count++;
            last=nums[i].b;
        }
    }
    printf("%d\n",count);
    return 0;
}
