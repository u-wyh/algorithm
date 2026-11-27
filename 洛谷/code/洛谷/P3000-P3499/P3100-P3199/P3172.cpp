// https://www.luogu.com.cn/problem/P3172
// 题意：输入四个正整数 N, K, L, H。
// 从闭区间 [L, H] 中可重复地选取 N
// 个整数（共 (H-L+1)^N 种有序选法），
// 统计这 N 个数的最大公约数恰好等于 K 的方案数。
// 输出方案数对 10^9+7 取模的结果。
// 数据范围：1 <= N, K <= 10^9，
// 1 <= L <= H <= 10^9，H - L <= 10^5。
// 算法标签：莫比乌斯反演、线性筛、快速幂
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MOD = 1e9+7;

int N,K,L,H;

int cnt;
int prime[MAXN];
bool vis[MAXN];
int mu[MAXN];

void prepare(int n){
    mu[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cnt]=i;;
            mu[i]=-1;
        }
        for(int j=1;j<=cnt&&(i*prime[j]<=n);j++){
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
}

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

signed main()
{
    prepare(100000);
    cin>>N>>K>>L>>H;

    int l=(L+K-1)/K;
    int r=H/K;

    if(l>r){
        cout<<0<<endl;
        return 0;
    }

    int ans=(l==1)?1:0;
    for(int d=1;d<=(r-l);d++){
        if(mu[d]==0){
            continue;
        }
        int c=(r/d)-(l-1)/d;
        ans+=mu[d]*(power(c,N)-c);
        ans%=MOD;
    }
    ans=(ans%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}