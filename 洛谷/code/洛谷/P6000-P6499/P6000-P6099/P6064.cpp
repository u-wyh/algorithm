// https://www.luogu.com.cn/problem/P6064
// 题意：将一天环形划分为 N 个时段，第 i 时段睡觉效用为 U_i，
// 共需睡 B 个时段（只能在边界入睡/醒来），每段连续睡眠的第 1 个时段不计效用
// 求最大总效用值。
// 数据范围：3 <= N <= 3830，2 <= B < N，
// 0 <= U_i <= 2 * 10^5。
// 算法标签：动态规划
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3900;

int dp[MAXN][MAXN][2];
int n,m,ans;
int arr[MAXN];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            dp[i][j][0]=dp[i][j][1]=INT_MIN;
        }
    }
    dp[1][1][1]=0;
    dp[1][0][0]=0;
    for(int i=2;i<=n;i++){
        dp[i][0][0]=dp[i-1][0][0];
        for(int j=1;j<=m;j++){
            dp[i][j][1]=max(dp[i-1][j-1][0],dp[i-1][j-1][1]+arr[i]);
            dp[i][j][0]=max(dp[i-1][j][0],dp[i-1][j][1]);
        }
    }
    ans=max(dp[n][m][0],dp[n][m][1]);
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            dp[i][j][1]=dp[i][j][0]=INT_MIN;
        }
    }
    dp[1][1][1]=arr[1];
    dp[1][0][0]=0;
    for(int i=2;i<=n;i++){
        dp[i][0][0]=dp[i-1][0][0];
        for(int j=1;j<=m;j++){
            dp[i][j][1]=max(dp[i-1][j-1][0],dp[i-1][j-1][1]+arr[i]);
            dp[i][j][0]=max(dp[i-1][j][0],dp[i-1][j][1]);
        }
    }
    ans=max(ans,dp[n][m][1]);
    cout<<ans<<endl;
    return 0;
}
