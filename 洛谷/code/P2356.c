// https://www.luogu.com.cn/problem/P2356
// 题意：n*n 矩阵，0 表示空地，非 0 表示该格敌人的分值。
// 选一个空地站立，消灭同行和同列的所有敌人，求最多得分。
// 若没有空地，输出 Bad Game!。
// 数据范围：1 <= n <= 1000，空地数 < 10000，每格敌人数 <= 1000。
#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1][n+1];
    int a[n+1],b[n+1];
    for(int i=0;i<=n;i++)
    {
        a[i]=0;
        b[i]=0;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&nums[i][j]);
            a[i]+=nums[i][j];
            b[j]+=nums[i][j];
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(a[i]==n)
            continue;
        for(int j=1;j<=n;j++)
        {
            if(b[j]==n)
                continue;
            ans=max(ans,a[i]+b[j]);
        }
    }
    if(ans==0)
        printf("Bad Game!\n");
    else
        printf("%d\n",ans);
    return 0;
}
