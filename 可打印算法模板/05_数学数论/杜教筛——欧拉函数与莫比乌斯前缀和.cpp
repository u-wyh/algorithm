// 用途：快速求欧拉函数与莫比乌斯函数的前缀和。
// 时间：依预处理阈值，约 O(n^(2/3))。
// 空间：约 O(n^(2/3))。
// 例题：https://www.luogu.com.cn/problem/P4213
// 题意：多次查询大范围内 φ 或 μ 的前缀和。
// 思路：用卷积恒等式递归计算前缀和，按相同商整段处理并记忆化。
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e6+5;

int cnt;
int prime[MAXN];
bool vis[MAXN];

int phi[MAXN];
int mu[MAXN];

unordered_map<int,int>mp_mu;
unordered_map<int,int>mp_phi;
// 大于预处理上限的前缀和才进入记忆化表。

void prepare(int n){
    // 线性筛出 φ、μ，随后原地转成各自的前缀和。
    mu[1]=1,phi[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            phi[i]=i-1;
            mu[i]=-1;
            prime[++cnt]=i;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=1;
            if(i%prime[j]==0){
                phi[i*prime[j]]=prime[j]*phi[i];
                mu[i*prime[j]]=0;
                break;
            }
            else{
                phi[i*prime[j]]=(prime[j]-1)*phi[i];
                mu[i*prime[j]]=-mu[i];
            }
        }
    }
    for(int i=1;i<=n;i++){
        mu[i]+=mu[i-1];
        phi[i]+=phi[i-1];
    }
}

int du_phi(int n){
    // 利用 Σφ * 1 = id，按相同的 floor(n/l) 一段段扣除贡献。
    if(n<MAXN){
        return phi[n];
    }
    if(mp_phi[n]){
        return mp_phi[n];
    }
    int ans=n*(n+1)/2;
    for(int l=2,r;l<=n;l=r+1){
        r=n/(n/l);
        ans-=(r-l+1)*du_phi(n/l);
    }
    mp_phi[n]=ans;
    return ans;
}

int du_mu(int n){
    // 利用 Σμ * 1 = ε，n>1 的总卷积值为 0。
    if(n<MAXN){
        return mu[n];
    }
    auto it = mp_mu.find(n);
    if(it != mp_mu.end()){
        return it->second;
    }
    int ans=1;
    for(int l=2,r;l<=n;l=r+1){
        r=n/(n/l);
        ans-=(r-l+1)*du_mu(n/l);
    }
    mp_mu[n]=ans;
    return ans;
}

signed main()
{
    prepare(MAXN-1);
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        cout<<du_phi(n)<<' '<<du_mu(n)<<endl;
    }
    return 0;
}
