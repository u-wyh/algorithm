// https://www.luogu.com.cn/problem/P4213
// 题意：多组数据，每组给一个正整数 n
// 求欧拉函数前缀和 sum_{i=1}^{n} phi(i) 和莫比乌斯函数前缀和 sum_{i=1}^{n} mu(i)。
// 数据范围：1 <= T <= 10，1 <= n < 2^31。
#include<bits/stdc++.h>
// 算法标签：杜教筛、线性筛、整除分块
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

void prepare(int n){
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
    if(n<MAXN){
        return mu[n];
    }
    if(mp_mu[n]){
        return mp_mu[n];
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