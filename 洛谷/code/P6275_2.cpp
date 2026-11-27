// https://www.luogu.com.cn/problem/P6275
// 题意：N*N 网格中 'W' 格不可装洒水器，'.' 格至多装一个甜玉米洒水器（覆盖左下方）或苜蓿洒水器（覆盖右上方）。
// 求使全网格每格恰好被一种洒水器覆盖的安装方案数（mod 10^9+7）。
// 数据范围：1 <= N <= 2000。
// 算法标签：动态规划
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 2005;
const int MOD = 1e9+7;
const int inv = 500000004;

int n;
int sum[MAXN];
int dp[MAXN][MAXN][2];
int p[MAXN*MAXN];
char s[MAXN][MAXN];

signed main()
{
    cin>>n;
    p[0]=1;
    for(int i=1;i<=n*n;i++){
        p[i]=(p[i-1]*2)%MOD;
    }
    for(int i=1;i<=n;i++){
        scanf("%s",s[i]+1);
        for(int j=1;j<=n;j++){
            sum[i]+=(s[i][j]=='.');
        }
    }
    dp[0][0][0]=dp[0][0][1]=1;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            if(i==0&&j==0){
                continue;
            }
            if(j>0){
                dp[i][j][0]=dp[i][j-1][0];
                if(s[i][j]=='.'){
                    dp[i][j][0]=(dp[i][j][0]+(dp[i][j-1][1]*inv)%MOD)%MOD;
                }
            }
            if(i>0){
                dp[i][j][1]=dp[i-1][j][1]*p[sum[i]]%MOD;
                if(s[i][j]=='.'){
                    dp[i][j][1]=(dp[i][j][1]+dp[i-1][j][0]*(p[sum[i]-1])%MOD)%MOD;
                }
            }
        }
    }
    int ans=(dp[n][n][0]+dp[n][n][1])%MOD;
    cout<<ans<<endl;
    return 0;
}