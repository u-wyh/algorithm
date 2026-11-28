// https://www.luogu.com.cn/problem/P1799
// 题意：给定长度为 n 的正整数序列，删去任意一些数，
// 保留其余数的相对顺序并从 1 重新编号。求数值等于新下标的元素最多有几个。
// 数据范围：n ≤ 1000，A_i 为正整数。
// 难度评分：1500（洛谷分级换算）
// 算法标签：动态规划

#include<bits/stdc++.h>
using namespace std;

int n;
int nums[1005];
int dp[1005][1005];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=i;j++){
            if(j>0){
                dp[i][j]=dp[i-1][j-1];
            }
            dp[i][j]=max(dp[i][j],dp[i-1][j]+(nums[i]==i-j));
        }
    }
    int ans=0;
    for(int j=0;j<=n;j++){
        ans=max(ans,dp[n][j]);
    }
    cout<<ans;
    return 0;
}
