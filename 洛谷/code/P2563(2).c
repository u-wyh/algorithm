#include <stdio.h>
#include <string.h>
#include <math.h>


int pan(int x) {
    for (int i = 2; i <= (int)sqrt(x); i++) {
        if (x % i == 0) return 0;
    }
    return 1;
}

int main()
{
    int su[47];
    int num=0;
    for (int i = 2; i <= 200; i++) {
        if (pan(i)) {
            su[++num] = i;
        }
    }
    int dp[47][201];
    for(int i=0;i<=200;i++)
        dp[0][i]=0;
    dp[0][0]=1;
    for(int i=1;i<=46;i++)
    {
        for(int j=0;j<=200;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(j>=su[i])
                dp[i][j]+=dp[i][j-su[i]];
        }
    }
    int n;
    while(scanf("%d",&n)==1)
    {
        printf("%d\n",dp[46][n]);
    }
}
