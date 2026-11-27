// https://www.luogu.com.cn/problem/P2727
// 题意：所有长度为 N 的二进制串（允许前导零）中，
// 选出至多有 L 个 1 的串并按数值升序排列。
// 输出第 i 个二进制串。
// 数据范围：1 <= N <= 31，0 <= L <= N，
// 保证第 i 个串存在。
// 算法标签：动态规划、组合数学
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n,len,m;
int dp[35][35];

signed main()
{
    cin>>n>>len>>m;
    for(int i=0;i<=len;i++){
        dp[0][i]=1;
    }
    for(int i=1;i<=n;i++){
        dp[i][0]=1;
        for(int j=1;j<=len;j++){
            dp[i][j]=dp[i-1][j]+dp[i-1][j-1];
        }
    }
    for(int i=n;i>=1;i--){
        int ans=0;
        if(dp[i-1][len]<m){
            ans=1;
            m-=dp[i-1][len];
            len--;
        }
        cout<<ans;
    }
    return 0;
}