#include<stdio.h>
#define Max 100000005

int flag[Max];
int dp[Max];

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int len,s,t,m;
    scanf("%d %d %d %d",&len,&s,&t,&m);
    int nums[m+1];
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&nums[i]);
        flag[nums[i]]=1;
    }
    memset(dp,1e9,sizeof(dp));
    for(int i=0;i<=len;i++)
    {
        if(i<s)
            dp[i]=0;
        for(int j=s;j<=t&&j<=i;j++)
            dp[i]=min(dp[i],dp[i-j]+flag[i]);
    }
    printf("%d\n",dp[len]);
    return 0;
}
