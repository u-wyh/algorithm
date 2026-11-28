// https://www.luogu.com.cn/problem/P4187
// 题意：有 M 种颜色、长度为 K 的图章，
// 每次可把长为 N 的画布中一段长为 K 的连续区间染成同色（后染覆盖先染），
// 要求最终整个画布都被染满
// 求共有多少种不同的最终状态（对 1e9+7 取模）。
// 数据范围：N, M, K <= 1e6。
// 难度评分：1800（洛谷分级换算）
// 算法标签：动态规划、前缀和优化、快速幂
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MOD = 1e9+7;
const int MAXN = 1e6+5;

int n,m,k;
int f[MAXN];
int g[MAXN];

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        a=(a*a)%MOD;
        b>>=1;
    }
    return ans;
}

signed main()
{
    cin>>n>>m>>k;
    if(k>n){
        cout<<0<<endl;
        return 0;
    }
    f[0]=1;
    for(int i=1;i<k;i++){
        f[i]=(m*f[i-1])%MOD;
        g[i]=(g[i-1]+f[i])%MOD;
    }
    for(int i=k;i<=n;i++){
        f[i]=(m-1)*(g[i-1]-g[i-k])%MOD;
        g[i]=(g[i-1]+f[i])%MOD;
    }
    int ans=power(m,n);
    ans=((ans-f[n])%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}