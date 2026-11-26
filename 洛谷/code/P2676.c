// https://www.luogu.com.cn/problem/P2676
// 题意：N 头奶牛各有身高 H_i，书架高度为 B。
// 选出尽量少的奶牛，使其身高之和不小于 B。
// 输出最少奶牛数目。
// 数据范围：1 <= N <= 20000，1 <= H_i <= 10000，1 <= B <= S < 2*10^9+7。
#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b)
{
    return (*(int *)b -*(int *)a);
}

int main()
{
    int n;
    long long m;
    scanf("%d %lld",&n,&m);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    qsort(nums+1,n,sizeof(int),cmp);
    //printf("%d\n",nums[n]);
    int i=1;
    long long sum=0;
    while(sum<m)
    {
        sum+=nums[i++];
    }
    printf("%d\n",i-1);
    return 0;
}
