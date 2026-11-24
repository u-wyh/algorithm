// 用途：用莫比乌斯反演计数区间内 gcd 恰为 K 的 N 元组。
// 时间：O(10^5+D log N)，D=⌊H/K⌋-⌈L/K⌉，含线性筛。
// 空间：O(10^5)。
// 注意：本实现按例题的 H-L≤10^5 固定筛到 10^5。
// 例题：https://www.luogu.com.cn/problem/P3172
// 题意：统计区间内 gcd 恰为 K 的 N 元组数量。
// 思路：先除以 K，再用莫比乌斯反演对公因子容斥。
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

    // 非全相等元组的 gcd 不超过 r-l；全为 1 的元组单独补回。
    int ans=(l==1)?1:0;
    for(int d=1;d<=(r-l);d++){
        if(mu[d]==0){
            continue;
        }
        int c=(r/d)-(l-1)/d;
        ans+=mu[d]*(power(c,N)-c); // 扣掉全相等元组，避免它们在各个 d 上重复出现。
        ans%=MOD;
    }
    ans=(ans%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}
