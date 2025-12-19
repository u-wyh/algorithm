#include<stdio.h>

int gcd(int a, int b)
{
    if(b == 0)  return a;
    else    return gcd(b, a%b);
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    int GCD=nums[1];
    for(int i=2;i<=n;i++)
        GCD=gcd(GCD,nums[i]);
    if(GCD!=1)
    {
        printf("INF\n");
        return 0;
    }
    int dp[1000105];
    for(int i=0;i<=1000104;i++)
        dp[i]=0;
    dp[0]=1;
    for(int i=0;i<=1000000;i++)
		if(dp[i])
		for(int j=1;j<=n;j++)
			dp[i+nums[j]]=1;
	int count=0;
    for(int i=1;i<=1000000;i++)
        if(!dp[i])
            count++;
    printf("%d\n",count);
    return 0;
}
