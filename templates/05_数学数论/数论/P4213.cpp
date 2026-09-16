// https://www.luogu.com.cn/problem/P4213
// 杜教筛适用于求积性函数前缀和的  时间复杂度为n的2/3次方
// 主要是构造出一个积性函数g  然后根据公式递推
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