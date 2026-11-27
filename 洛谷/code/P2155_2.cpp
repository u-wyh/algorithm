// https://www.luogu.com.cn/problem/P2155
// 题意：T 组询问，每组给定 N, M，求 [1, N!] 中与 M! 互质的数的个数。
// 每组输出答案对质数 R 取模的结果。
// 数据范围：1 <= M <= N <= 10^7，1 <= T <= 10^4，2 <= R <= 10^9+10。
#include<bits/stdc++.h>
// 算法标签：线性筛、逆元、快速幂
using namespace std;
#define int long long
const int MAXN = 1e7+5;

int n,m,mod;
int f[MAXN];

int pri[MAXN];
int len;
bool vis[MAXN];

int fac[MAXN];
int inv[MAXN];

int power(int a,int b,int mod){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%mod;
        }
        b>>=1;
        a=(a*a)%mod;
    }
    return ans;
}

void prepare(int n){
    vis[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            pri[++len]=i;
        }
        for(int j=1;j<=len&&(i*pri[j]<=n);j++){
            vis[i*pri[j]]=true;
            if(i%pri[j]==0){
                break;
            }
        }
    }

    f[1]=1;
    for(int i=2;i<=n;i++){
        if(vis[i]){
            f[i]=f[i-1]*i;
        }
        else{
            f[i]=f[i-1]*(i-1);
        }
        f[i]%=mod;
    }

    fac[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=(fac[i-1]*i)%mod;
    }
    int limit=min(mod-1,n);
    inv[limit]=power(fac[limit],mod-2,mod);
    for(int i=limit-1;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%mod;
    }
}

int compute(int n,int m){
    int ans=f[m];

    if(n<mod){
        ans=ans*fac[n]%mod;
        ans=ans*inv[m]%mod;
        return ans;
    }

    if(m<mod){
        return 0;
    }

    if(n>=2*mod){
        return 0;
    }

    ans=ans*fac[n-mod]%mod;
    ans=ans*inv[m-mod]%mod;

    return ans;
}

signed main()
{
    int T;
    cin>>T>>mod;
    prepare(10000000);
    while(T--){
        cin>>n>>m;
        cout<<compute(n,m)<<endl;
    }
    return 0;
}