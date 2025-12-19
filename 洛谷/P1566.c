#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int compare(const void *a, const void *b)
{
    int arg1 = *((int*)a);
    int arg2 = *((int*)b);

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        int nums[n+1];
        int sum=0;
        nums[0]=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&nums[i]);
            sum+=nums[i];
        }
        qsort(nums,n+1,sizeof(int),compare);
        /*for(int i=0;i<=n;i++)
        {
            printf("%3d",nums[i]);
        }
        printf("\n");*/
        int dp[sum+1];
        memset(dp,0,sizeof(dp));
        dp[0]=1;
        int ans=0;
        for(int i=1;i<=n;i++)
        {
            /*for(int k=1;k<=sum;k++)
            {
                printf("%d",dp[k]);
            }
            printf("\n");*/
            //ans+=dp[nums[i]];
            for(int j=sum;j>=nums[i];j--)
            {
                dp[j]+=dp[j-nums[i]];
            }
        }
        for(int i=1;i<=n;i++)
        {
            ans+=dp[nums[i]];
        }
        printf("%d\n",ans-n);
    }
    return 0;
}
