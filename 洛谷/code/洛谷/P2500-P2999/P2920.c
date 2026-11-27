// https://www.luogu.com.cn/problem/P2920
// 题意：输入工作数 N，
// 以及每项工作需要的连续耗时 T_i 和最晚完成截止时间 S_i。
// 约翰从 0 时刻或之后的某个整数时刻开始依次完成所有工作，
// 每项工作开始后不能中断且同时只能做一项，要求每项都在 S_i 或之前完成。
// 计算能按时完成所有工作的最晚开始时刻。
// 输出一行一个整数，表示最晚开始时间；若无论何时开始都无法按时完成则输出 -1。
// 数据范围：对于 100% 的数据，1 <= N <= 1000，
// 1 <= T_i <= 1000，1 <= S_i <= 10^6。
// 算法标签：贪心、排序
#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int a,b,c;
}time;

int min(int a,int b)
{
    return a<b?a:b;
}

int cmp(const void *a,const void *b)
{
    time *ta=(time *)a;
    time *tb=(time *)b;

    return ta->b - tb->b;
}

int main()
{
    int n;
    scanf("%d",&n);
    time nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&nums[i].a,&nums[i].b);
        nums[i].c=nums[i].b-nums[i].a;
    }
    qsort(nums+1,n,sizeof(time),cmp);
    int k=1,ans=1e6;
    for(int i=1;i<=n;i++)
    {
        if(i==1)
        {
            if(nums[1].c<0)
            {
                printf("-1\n");
                return 0;
            }
            else
            {
                ans=min(ans,nums[1].c);
                nums[1].c=nums[1].a;
            }
        }
        else
        {
            if(nums[i].c<nums[i-1].c)
            {
                printf("-1\n");
                return 0;
            }
            else
            {
                ans=min(ans,nums[i].c-nums[i-1].c);
                nums[i].c=nums[i-1].c+nums[i].a;
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
