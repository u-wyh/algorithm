// https://www.luogu.com.cn/problem/P7961
// 题意：给定整数 n, m, k 与数组 v_0..v_m。
// 对长为 n、元素均在 [0, m] 内的非负整数序列 {a_i}，其权值为 ∏_{i=1}^n v_{a_i}。
// 若 S = ∑_{i=1}^n 2^{a_i} 的二进制表示中 1 的个数不超过 k，则该序列合法。
// 求所有合法序列的权值和对 998244353 取模的结果。
// 第一行输入 n, m, k，第二行输入 v_0..v_m。
// 输出一行一个整数。
// 数据范围：1 <= k <= n <= 30，0 <= m <= 100，1 <= v_i < 998244353。
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 35;
const int MAXM = 105;

int n,m,limit;
int val[MAXM];
int dp[MAXM][MAXN][MAXN][MAXN];
int power[MAXM][MAXN];
int c[MAXN][MAXN];

inline int onecount(int x){
    int ans=0;
    while(x){
        if(x&1){
            ans++;
        }
        x>>=1;
    }
    return ans;
}

signed main()
{
    cin>>n>>m>>limit;
    for(int i=0;i<=m;i++){
        cin>>val[i];
    }

    for(int i=0;i<=n;i++){
        c[i][0]=c[i][i]=1;
        for(int j=1;j<i;j++){
            c[i][j]=(c[i-1][j-1]+c[i-1][j])%MOD;
        }
    }
    for(int i=0;i<=m;i++){
        power[i][0]=1;
        for(int j=1;j<=n;j++){
            power[i][j]=(power[i][j-1]*val[i])%MOD;
        }
    }
    dp[0][0][0][0]=1;
    for(int i=0;i<=m;i++){
        for(int j=0;j<=n;j++){
            for(int k=0;k<=30;k++){
                for(int p=0;p<=limit;p++){
                    if(dp[i][j][k][p]==0){
                        continue;
                    }
                    for(int t=0;t<=n-j;t++){
                        int jj=j+t;
                        int sum=k+t;
                        int pp=p+(sum&1);
                        if(pp>limit){
                            continue;
                        }
                        int kk=(sum>>1);
                        dp[i+1][jj][kk][pp]=(dp[i+1][jj][kk][pp]+c[n-j][t]*power[i][t]%MOD*dp[i][j][k][p]%MOD)%MOD;
                    }
                }
            }
        }
    }

    int ans=0;
    for(int i=0;i<=30;i++){
        for(int j=0;j<=limit;j++){
            if(dp[m+1][n][i][j]==0){
                continue;
            }
            int ones=j+onecount(i);
            if(ones>limit){
                continue;
            }
            ans=(ans+dp[m+1][n][i][j])%MOD;
        }
    }
    cout<<ans<<endl;
    return 0;
}