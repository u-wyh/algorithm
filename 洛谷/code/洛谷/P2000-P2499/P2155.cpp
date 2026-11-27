// https://www.luogu.com.cn/problem/P2155
// 题意：T 组询问，每组给定 N, M，
// 求 [1, N!] 中与 M! 互质的数的个数。
// 每组输出答案对质数 R 取模的结果。
// 数据范围：1 <= M <= N <= 10^7，1 <= T <= 10^4，
// 2 <= R <= 10^9+10。
// 算法标签：线性筛、快速幂、逆元
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e7+5;

int mod;

bool isprime[MAXN];
int prime[MAXN];

int fac[MAXN];
int phi[MAXN];

void prepare(int n){
    int cnt=0;
    isprime[0]=isprime[1]=1;
    for(int i=2;i<=n;i++){
        if(isprime[i]==0){
            prime[++cnt]=i;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            isprime[i*prime[j]]=prime[j];
            if(i%prime[j]==0){
                break;
            }
        }
    }
    fac[0]=phi[0]=1;
    for(int i=1;i<=n;i++){
        int tmp=i;
        while(tmp%mod==0){
            tmp/=mod;
        }
        fac[i]=fac[i-1]*i%mod;
        tmp=i-1+isprime[i];
        while(tmp%mod==0){
            tmp/=mod;
        }
        phi[i]=phi[i-1]*tmp%mod;
    }
}

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%mod;
        }
        a=(a*a)%mod;
        b>>=1;
    }
    return ans;
}

signed main()
{
    int T;
    cin>>T>>mod;
    prepare(10000000);
    while(T--){
        int n,m;
        cin>>n>>m;
        int ans=fac[n]*phi[m]%mod*power(fac[m],mod-2)%mod;
        // cout<<ans<<' ';
        if(n/mod>m/mod){
            ans=0;
        }
        cout<<ans<<endl;
    }
    return 0;
}