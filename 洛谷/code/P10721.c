#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int max(int a,int b)
{
    return  a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int a[n+1];
    a[0]=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    int m;
    scanf("%d",&m);
    getchar();
    char str[m+1];
    fgets(str,m+1,stdin);
    //printf("%c",str[m-1]);
    int nums[m];
    int k=0;
    for(int i=0;i<m-2;i++)
    {
        if(str[i]=='a'&&str[i+1]=='b'&&str[i+2]=='c')
        {
            nums[k++]=1;
            i+=2;
        }
        else
            nums[k++]=0;
    }
    /*for(int i=0;i<k;i++)
        printf("%3d",nums[i]);
    printf("\n");
    //printf("%d\n",k);*/
    int sum[k];
    sum[0]=nums[0];
    for(int i=1;i<k;i++)
    {
        if(nums[i]&&sum[i-1]!=0)
            sum[i]=sum[i-1]+1;
        else if(nums[i])
            sum[i]=1;
        else
            sum[i]=0;
    }
    /*for(int i=0;i<k;i++)
        printf("%3d",sum[i]);
    printf("\n");*/
    int dp[k];
    for(int i=0;i<k;i++)
    {
        dp[i]=a[nums[i]];
    }
    dp[0]=a[nums[0]];
    for(int i=1;i<k;i++)
    {
        dp[i]+=dp[i-1];
        if(nums[i])
        {
            for(int j=1;j<sum[i];j++)
            {
                if(nums[i-j])
                    dp[i]=max(dp[i],dp[i-j-1]+a[j+1]);
            }
        }
        else
            dp[i]=dp[i-1];
    }
    /*for(int i=0;i<k;i++)
        printf("%3d",dp[i]);
    printf("\n");*/
    printf("%d\n",dp[k-1]);
    return 0;
}
