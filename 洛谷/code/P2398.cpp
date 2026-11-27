// https://www.luogu.com.cn/problem/P2398
// 题意：给定整数 n，求 sum_{i=1..n} sum_{j=1..n} gcd(i, j)。
// 输出计算结果。
// 数据范围：n <= 10^5。
#include<bits/stdc++.h>
// 算法标签：线性筛、欧拉函数、前缀和
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int phi[MAXN];
int prime[MAXN];
int cnt=0;
bool vis[MAXN];
int sum[MAXN];

void euler(int n){
    phi[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cnt]=i;
            phi[i]=i-1;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=1;
            if(i%prime[j]==0){
                phi[i*prime[j]]=prime[j]*phi[i];
            }
            else{
                phi[i*prime[j]]=(prime[j]-1)*phi[i];
            }
        }
    }
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+phi[i];
    }
}

signed main()
{
    int n;
    cin>>n;
    euler(n);
    long long ans=0;
    for(int i=1;i<=n;i++){
        ans+=(2ll*sum[n/i]-1)*i;
    }
    cout<<ans<<endl;
    return 0;
}