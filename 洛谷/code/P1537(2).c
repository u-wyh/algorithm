#include<stdio.h>

int main()
{
    int k=0;
    int num[7];
    while(scanf("%d %d %d %d %d %d",&num[1],&num[2],&num[3],&num[4],&num[5],&num[6])==6
          &&(num[1]+num[2]+num[3]+num[4]+num[5]+num[6])!=0)
    {
        int sum=0;
        k++;
        printf("Collection #%d:\n",k);
        sum=num[1]+num[2]*2+num[3]*3+num[4]*4+num[5]*5+num[6]*6;
        int h=(num[1]+num[2]+num[3]+num[4]+num[5]+num[6]);
        if(sum%2==1)
        {
            printf("Can't be divided.\n");
            printf("\n");
            continue;
        }
        int dp[sum/2+1];
        for(int i=0;i<=sum/2;i++)
        {
            dp[i]=0;
        }
        dp[0]=1;
        for(int i=1;i<=6;i++)
        {
            for(int j=sum/2;j>=1;j--)
            {
                for(int k=1;k<=num[i]&&j>=k*i;k++)
                    dp[j]|=dp[j-k*i];
            }
        }
        if(dp[sum/2])
        {
            printf("Can be divided.\n");
            printf("\n");
            continue;
        }
        else
        {
            printf("Can't be divided.\n");
            printf("\n");
            continue;
        }
    }
    return 0;
}
