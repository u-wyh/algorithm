#include<stdio.h>

int main()
{
    int nums[7];
    for(int i=1;i<=6;i++)
    {
        scanf("%d",&nums[i]);
    }
    int count[7]={0,1,2,3,5,10,20};
    int dp[1001];
    for(int i=1;i<=1000;i++)
        dp[i]=0;
    dp[0]=1;

    int ans=0;
    for(int i=1;i<=1000;i++)
    {
        if(dp[i])
            ans++;
    }
    printf("%d\n",ans);
    return 0;
}
