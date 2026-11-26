// https://www.luogu.com.cn/problem/P1610
// 题意：洞内有 n 盏灯，各有互不相等的位置 p_i，安全距离为 dist。
// 若第 i-1 盏与第 i+1 盏灯的距离 <= dist，则第 i 盏灯可关掉。
// 首尾（距洞口最近和最远）两盏灯必须亮着，求一段区域里最多可关几盏灯。
// 输出最多能关掉的灯数。
// 数据范围：
// 1 <= n <= 10^5（灯的数量）
// dist 在 int 整型范围内（p_i 互不相等）
#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b)
{
    return (*(int *)a-*(int *)b);
}

int main()
{
    int n,m,count=0;
    scanf("%d %d",&n,&m);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    qsort(nums+1,n,sizeof(int),cmp);
    //printf("%d\n",nums[n]);
    for(int i=2;i<=n-1;i++)
    {
        if(nums[i+1]-nums[i-1]<=m)
        {
            nums[i]=nums[i-1];
            count++;
        }
    }
    printf("%d\n",count);
    return 0;
}
