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
    int dp[201];
    for(int i=0;i<=200;i++)
        dp[i]=0;
    dp[0]=1;
    for(int i=1;i<=46;i++)
    {
        for(int j=su[i];j<=200;j++)
        {
            dp[j]+=dp[j-su[i]];
        }
    }
    int n;
    while(scanf("%d",&n)==1)
    {
        printf("%d\n",dp[n]);
    }
}
