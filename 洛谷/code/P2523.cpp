// https://www.luogu.com.cn/problem/P2523
// 题意：T 组数据，n 个人选 1~n 的编号 a_i，依次尝试坐 a_i, a_i+1, ... 直到位置 n。
// 其中 m 个人编号已固定为 q_i，求所有人都能坐下的方案数。
// 每组输出 YES ans（模 M）或 NO。
// 数据范围：1 <= T <= 10，1 <= n <= 300，0 <= m <= n，2 <= M <= 10^9。
#include<bits/stdc++.h>
// 算法标签：动态规划、组合数学
using namespace std;
#define int long long
const int MAXN = 305;

int comb[MAXN][MAXN];
int dp[MAXN][MAXN];
int sum[MAXN];

signed main()
{
    int T;
    cin>>T;
    while(T--){
        int n,m,mod;
        cin>>n>>m>>mod;
        comb[0][0]=1;
        for(int i=1;i<=n;i++){
            comb[i][0]=comb[i][i]=1;
            for(int j=1;j<i;j++){
                comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%mod;
            }
        }
        for(int i=1;i<=n+1;i++){
            sum[i]=1;//这里添加一个位置 用于判断
        }
        for(int i=1;i<=m;i++){
            int u,v;
            cin>>u>>v;
            sum[v]--;
        }
        for(int i=1;i<=n+1;i++){
            if(sum[i-1]<0){
                sum[i]+=sum[i-1];
                sum[i-1]=0;
            }
        }
        if(sum[n+1]<=0){
            cout<<"NO"<<endl;
            continue;
        }
        for(int i=1;i<=n;i++){
            sum[i]+=sum[i-1];
            // cout<<sum[i]<<' ';
        }
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n-m;j++){
                dp[i][j]=0;
            }
        }
        dp[0][0]=1;
        for(int i=1;i<=n;i++){
            for(int j=sum[i];j<=n-m;j++){
                for(int k=0;k<=j;k++){
                    dp[i][j]=(dp[i][j]+dp[i-1][k]*comb[n-m-k][j-k])%mod;
                }
            }
        }
        cout<<"YES "<<dp[n][n-m]<<endl;
    }
    return 0;
}