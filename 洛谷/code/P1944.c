#include<stdio.h>
#include<string.h>
#define Max 1000000

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    char str[Max];
    fgets(str,Max,stdin);
    int n=strlen(str)-1;
    int dp[n];
    for(int i=0;i<n;i++)
        dp[i]=0;
    for(int i=1;i<n;i++)
    {
        if(str[i]=='('||str[i]=='[')
            dp[i]=0;
        else
        {
            int p=dp[i-1];
            if((str[i]==']'&&str[i-p-1]=='[')||(str[i]==')'&&str[i-p-1]=='('))
                dp[i]=dp[i-1]+2+((i-p-2>=0)?dp[i-p-2]:0);
        }
    }
    int max=0,k;
    for(int i=n;i>=0;i--)
    {
        if(dp[i]>=max)
        {
            max=dp[i];
            k=i;
        }
    }
    for(int i=k-max+1;i<=k;i++)
        printf("%c",str[i]);
    printf("\n");
    return 0;
}
