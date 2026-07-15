#include<stdio.h>
#include<string.h>
#include<limits.h>
#define Max 2001

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n1,n2;
    char s1[Max],s2[Max];
    fgets(s1,Max,stdin);
    n1=strlen(s1)-1;
    //printf("%d\n",n1);
    fgets(s2,Max,stdin);
    n2=strlen(s2)-1;
    //printf("%d\n",n2);
    int dp[n1+1][n2+1];
    for(int i=0;i<=n1;i++)
    {
        for(int j=0;j<=n2;j++)
        {
            dp[i][j]=INT_MAX;
            if(i==0)
                dp[0][j]=j;
            if(j==0)
                dp[i][0]=i;
        }
    }
    for(int i=1;i<=n1;i++)
    {
        for(int j=1;j<=n2;j++)
        {
            if(s1[i-1]==s2[j-1])
                dp[i][j]=min(dp[i][j],dp[i-1][j-1]);
            if(s1[i-1]!=s2[j-1])
                dp[i][j]=min(dp[i][j],dp[i-1][j-1]+1);
            dp[i][j]=min(min(dp[i-1][j]+1,dp[i][j-1]+1),dp[i][j]);
        }
    }
    printf("%d\n",dp[n1][n2]);
    return 0;
}
