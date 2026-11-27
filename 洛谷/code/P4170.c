// https://www.luogu.com.cn/problem/P4170
// 题意：有一条长为 n 的无色木板，每次可以把连续一段涂成某种颜色（后涂覆盖先涂），给一个长度为 n 的大写字母目标串，求最少需要涂色多少次。
// 数据范围：1 <= n <= 50。
#include<stdio.h>
#include<string.h>
#include<limits.h>
#define Max 51
// 算法标签：区间动态规划

static int dp[Max][Max];

int min(int a,int b)
{
    return a<b?a:b;
}

int compute(char *s,int n)
{
    for(int i=0;i<n-1;i++)
    {
        dp[i][i]=1;
        dp[i][i+1]=(s[i]==s[i+1])?1:2;
    }
    dp[n-1][n-1]=1;
    int ans;
    for(int l=n-3;l>=0;l--)
    {
        for(int r=l+2;r<n;r++)
        {
            if(s[l]==s[r])
                dp[l][r]=dp[l][r-1];
            else
            {
                ans=dp[l][r-1]+1;
                for(int m=l;m<r;m++)
                    ans=min(ans,dp[l][m]+dp[m+1][r]);
                dp[l][r]=ans;
            }
        }
    }
    return dp[0][n-1];
}

int main()
{
    char s[Max];
    fgets(s,Max,stdin);
    int n=strlen(s)-1;
    //for(int i=0;i<n;i++)
        //printf("%c\n",s[i]);
    //printf("%d\n",n);
    //n是实际有效字符串长度
    printf("%d\n",compute(s,n));
    return 0;
}
