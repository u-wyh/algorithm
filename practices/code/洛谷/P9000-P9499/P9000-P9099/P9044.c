// https://www.luogu.com.cn/problem/P9044
// 题意：n 个人得分分别为 a_i，至少颁发 k 件礼物。
// 要求若 a_x >= a_y 且 y 拿到礼物则 x 也必须拿到礼物。
// 求满足条件的最小颁发礼物数量。
// 数据范围：1 <= k <= n <= 2000，
// 1 <= a_i <= 120。
// 难度评分：800（洛谷分级换算）
// 算法标签：排序
#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b)
{
    return (*(int *)b-*(int *)a);
}
int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    qsort(nums+1,n,sizeof(int),cmp);
    //printf("%d\n",nums[1]);
    int i;
    for(i=k+1;i<=n;i++)
    {
        if(nums[i]<nums[k])
            break;
    }
    printf("%d\n",i-1);
    return 0;
}
