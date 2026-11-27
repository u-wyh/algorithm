// https://www.luogu.com.cn/problem/P2051
// 题意：在 n 行 m 列的棋盘上放若干炮，也可以一个不放。
// 同一行或同一列的两门炮之间恰好隔一门炮时会互相攻击。
// 求没有炮互相攻击的摆法数，对 9999973 取模。
// 数据范围：1 ≤ n,m ≤ 100。
// 算法标签：动态规划、组合数学

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 9999973;

int n,m;
int f[105][105][105];

int C(int a,int b){
    int ans=1;
    for(int i=1;i<=min(b,a-b);i++){
        ans*=(a-i+1);
        ans/=i;
        ans%=MOD;
    }
    return ans;
}

signed main()
{
    cin>>n>>m;
    f[0][0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            for(int k=0;k<=m-j;k++){
                f[i][j][k]+=f[i-1][j][k];
                if(k>=1){
                    f[i][j][k]+=f[i-1][j+1][k-1]*(j+1);
                }
                if(j>=1){
                    f[i][j][k]+=f[i-1][j-1][k]*(m-j-k+1);
                }
                if(k>=1){
                    f[i][j][k]+=f[i-1][j][k-1]*j*(m-j-k+1);
                }
                if(k>=2){
                    f[i][j][k]+=f[i-1][j+2][k-2]*C(j+2,2);
                }
                if(j>=2){
                    f[i][j][k]+=f[i-1][j-2][k]*C(m-j-k+2,2);
                }
                f[i][j][k]%=MOD;
            }
        }
    }
    int ans=0;
    for(int i=0;i<=m;i++){
        for(int j=0;j<=m-i;j++){
            ans+=f[n][i][j];
            ans%=MOD;
        }
    }
    cout<<ans<<endl;
    return 0;
}
