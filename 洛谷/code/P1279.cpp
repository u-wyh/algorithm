// https://www.luogu.com.cn/problem/P1279
// 题意：给两个字符串，可在各自任意位置插入空格，使它们等长后逐列比较。
// 两个字母的代价是 ASCII 码差的绝对值，字母和空格配对代价是 K，两格都空代价为 0。
// 求所有对齐方式中的最小总代价。
// 数据范围：两串长度均不超过 2000，字符均为小写英文字母，1 ≤ K ≤ 100。

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2005;

char s1[MAXN];
char s2[MAXN];
int m,n,k;
int dp[MAXN][MAXN];

int main()
{
    cin>>s1>>s2>>k;
    n=strlen(s1);
    m=strlen(s2);
    //cout<<m<<n;
    for(int i=0;i<=n;i++){
        dp[i][0]=i*k;
    }
    for(int j=0;j<=m;j++){
        dp[0][j]=j*k;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            dp[i][j]=min(dp[i][j-1]+k,min(dp[i-1][j]+k,dp[i-1][j-1]+abs(int(s1[i-1]-s2[j-1]))));
        }
    }
    cout<<dp[n][m];
    return 0;
}
