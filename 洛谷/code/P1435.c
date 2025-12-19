#include<stdio.h>
#include<string.h>
#define Max 1001

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n;
    char str[Max];
    fgets(str,Max,stdin);
    n=strlen(str)-1;
    if(n==0)
    {
        printf("0\n");
        return 0;
    }
    int dp[n][n];
    for(int i=0;i<n;i++)
    {
        for(int j=i;j<n;j++)
        {
            if(i==j)
                dp[i][j]=0;
            if(j==i+1)
            {
                if(str[i]==str[j])
                    dp[i][j]=0;
                else
                    dp[i][j]=1;
            }
        }
    }
    for(int i=n-3;i>=0;i--)
    {
        for(int j=i+2;j<n;j++)
        {
            if(str[i]==str[j])
                dp[i][j]=dp[i+1][j-1];
            else
            {
                dp[i][j]=min(dp[i+1][j],dp[i][j-1])+1;
            }
        }
    }
    printf("%d",dp[0][n-1]);
    return 0;
}
