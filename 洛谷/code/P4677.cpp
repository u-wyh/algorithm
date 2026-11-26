// https://www.luogu.com.cn/problem/P4677
// 题意：一条直线上顺次有 n 个村庄且已知相邻距离 d_i，从中选 m 个建小学，求所有村庄到最近小学的距离总和最小值。
// 数据范围：1 <= m <= n < 500，1 <= d_i <= 100。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;

int n,m;
int arr[MAXN];
int f[MAXN][MAXN],dp[MAXN][MAXN];

int main()
{
    cin>>n>>m;
    for(int i=2;i<=n;i++){
        cin>>arr[i];
        arr[i]+=arr[i-1];
    }
    for(int l=1;l<=n;l++){
        for(int r=l;r<=n;r++){
            int mid=(l+r)/2;
            for(int k=l;k<=r;k++){
                f[l][r]+=abs(arr[mid]-arr[k]);
            }
        }
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            dp[i][j]=2e9;
        }
    }
    dp[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(j>=i){
                dp[i][j]=0;
            }
            else{
                for(int k=0;k<=i;k++){
                    dp[i][j]=min(dp[i][j],dp[k][j-1]+f[k+1][i]);
                }
            }
        }
    }
    cout<<dp[n][m]<<endl;
    return 0;
}
