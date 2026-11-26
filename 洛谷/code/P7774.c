// https://www.luogu.com.cn/problem/P7774
// 题意：给定 N 个初始角 a_i，回答 M 个目标角 b_i 能否通过若干个 a_i（可重复或不用）做加减运算在模 360 度意义下得到，输出 YES/NO。
// 数据范围：1 <= N, M <= 10，0 < a_i, b_i < 360。
#include<stdio.h>

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    int dp[361];
    for(int i=0;i<=360;i++)
        dp[i]=0;
    dp[0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=360;j++)
        {
            if(j>=nums[i])
                dp[j]|=dp[j-nums[i]];
            else
                dp[j]|=dp[(j+nums[i])%360];
        }
    }
    int nums2[m+1];
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&nums2[i]);
        if(dp[nums2[i]])
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
