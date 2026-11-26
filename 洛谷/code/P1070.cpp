// https://www.luogu.com.cn/problem/P1070
// 题意：环形路上有 n 段，每段在 m 个时刻分别有若干金币。
// 每次在任意工厂购买一个机器人，设它顺时针走 1 到 p 步，每秒走一段并收走当时的金币。
// 一个走完立刻再买，任一时刻只有一个在走。
// 求 m 秒内金币总收入减购买成本的最大值。
// 数据范围：2 ≤ n ≤ 1000，1 ≤ p ≤ m ≤ 1000，每段每秒金币和单个机器人成本均在 [1,100]。

#include<bits/stdc++.h>
using namespace std;

int n,m,p,x;
int dp[1005][1005];
int sum[1005][1005];
int a[1005][1005];

int main()
{
    cin>>n>>m>>p;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>x;
            sum[(n-j%n+i)%n+1][j]=x;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=2;j<=m;j++){
            sum[i][j]+=sum[i][j-1];
        }
    }
    for(int i=1;i<=n;i++){
        cin>>x;
        for(int j=1;j<=m;j++){
            a[(n-j%n+i)%n+1][j]=x;
        }
    }
    for(int i=1;i<=m;i++){
        for(int j=i;j<=m;j++){
            dp[i][j]=-1e9;
        }
    }
    for(int len=1;len<=m;len++){
        for(int i=1;i+len-1<=m;i++){
            int j=i+len-1;
            for(int k=i;k<j;k++){
                dp[i][j]=max(dp[i][j],dp[i][k]+dp[k+1][j]);
            }
            if(j-i>=p){
                continue;
            }
            for(int k=1;k<=n;k++){
                dp[i][j]=max(dp[i][j],sum[k][j]-sum[k][i-1]-a[k][i]);
            }
        }
    }
    cout<<dp[1][m]<<endl;
    return 0;
}
