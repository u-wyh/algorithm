// https://www.luogu.com.cn/problem/P10721
// 题意：给一个小写字符串和 n 个分值。
// 一段连续子串若恰好由 k 个 abc 拼成，可以得 a[k] 分。
// 挑若干互不重叠的计分段，其他字符不计分。
// 输出最大总得分。
// 数据范围：1 ≤ n ≤ 20，1 ≤ m ≤ 10^5，
// 1 ≤ a[k] ≤ 1000，只有 1 ≤ k ≤ n 可计分。
// 难度评分：1300（洛谷分级换算）
// 算法标签：字符串扫描、动态规划

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
