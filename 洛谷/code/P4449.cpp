// https://www.luogu.com.cn/problem/P4449
// 题意：给定全局常数 k 和 T 组询问 (n, m)
// 每组求 sum_{i=1}^n sum_{j=1}^m gcd(i, j)^k 对 10^9 + 7 取模的结果。
// 数据范围：1 <= T <= 2 * 10^3，1 <= n, m, k <= 5 * 10^6。
#include<bits/stdc++.h>
// 算法标签：莫比乌斯反演、线性筛、数论分块
using namespace std;
#define int long long
const int MAXN = 5e6+5;
const int MOD = 1e9+7;

int n,m,k;

int cnt;
bool vis[MAXN];
int prime[MAXN];

int mu[MAXN];

int g[MAXN];
int p[MAXN];

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

void prepare(int n){
    mu[1]=1;
    g[1]=1;

    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cnt]=i;
            mu[i]=-1;
            p[i]=power(i,k);
            g[i]=(p[i]-1+MOD)%MOD;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]==0){
                mu[i*prime[j]]=0;
                g[i*prime[j]]=g[i]*p[prime[j]]%MOD;
                break;
            }
            else{
                mu[i*prime[j]]=-mu[i];
                g[i*prime[j]]=g[i]*g[prime[j]]%MOD;
            }
        }
    }
    for(int i=1;i<=n;i++){
        g[i]=(g[i-1]+g[i])%MOD;
    }
}

int compute(int n,int m){
    int ans=0;
    for(int l=1,r;l<=n;l=r+1){
        r=min(n/(n/l),m/(m/l));
        ans=(ans+((n/l)*(m/l)%MOD*((g[r]-g[l-1]+MOD)%MOD))%MOD)%MOD;
    }
    return ans;
}

signed main()
{
    int T;
    cin>>T>>k;
    prepare(MAXN-1);
    while(T--){
        cin>>n>>m;
        if(n>m){
            swap(n,m);
        }
        cout<<compute(n,m)<<endl;
    }
    return 0;
}