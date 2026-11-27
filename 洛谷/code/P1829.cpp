// https://www.luogu.com.cn/problem/P1829
// 题意：给定 n 行 m 列的表，第 i 行第 j 列填 i 和 j 的最小公倍数。求全表总和对 20101009 取模的值。
// 数据范围：1 ≤ n,m ≤ 10^7。
// 算法标签：莫比乌斯反演、数论分块、线性筛

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 20101009;
const int MAXN = 1e7+5;

int mu[MAXN];
long long pre[MAXN];

bool vis[MAXN];
int prime[MAXN];
int cnt;

void prepare(int n){
    mu[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cnt]=i;
            mu[i]=-1;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]==0){
                mu[i*prime[j]]=0;
                break;
            }
            else{
                mu[i*prime[j]]=-mu[i];
            }
        }
    }
    for(int i=1;i<=n;i++){
        pre[i]=(pre[i-1]+mu[i]*i%MOD*i%MOD)%MOD;
    }
}

long long G(int n,int m){
    return (1ll*(n+1)*n/2%MOD)*(1ll*m*(m+1)/2%MOD)%MOD;
}

long long F(int n,int m){
    long long ans=0;
    for(int l=1,r;l<=n;l=r+1){
        r=min(n/(n/l),m/(m/l));
        ans=(ans+1ll*(pre[r]-pre[l-1])*G(n/l,m/l)%MOD+MOD)%MOD;
    }
    return ans;
}

signed main()
{
    int n,m;
    cin>>n>>m;
    if(n>m){
        swap(n,m);
    }
    prepare(n);
    long long ans=0;
    for(int l=1,r;l<=n;l=r+1){
        r=min(n/(n/l),m/(m/l));
        ans=(ans+1ll*(r-l+1)*(l+r)/2%MOD*F(n/l,m/l)%MOD)%MOD;
    }
    cout<<ans<<endl;
    return 0;
}