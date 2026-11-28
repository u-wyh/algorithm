// https://www.luogu.com.cn/problem/P1094
// 题意：有 n 件不同价格的纪念品，把全部纪念品分组。
// 每组只有一件或两件，组内价格和不超过 w。输出最少组数。
// 数据范围：1 ≤ n ≤ 30000，80 ≤ w ≤ 200，
// 5 ≤ P[i] ≤ w。
// 难度评分：900（洛谷分级换算）
// 算法标签：贪心、双指针、排序

#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a ,const void *b)
{
    return (*(int *)a-*(int *)b);
}

int main()
{
    int m,n;
    scanf("%d %d",&m,&n);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    qsort(nums+1,n,sizeof(int ),cmp);
    int left=1,right=n,ans=0;
    while(left<=right)
    {
        if(nums[left]+nums[right]<=m)
        {
            left++;
            right--;
            ans++;
        }
        else
        {
            right--;
            ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}
