// https://www.luogu.com.cn/problem/P1390
// 题意：给 n，枚举 1 到 n 之间的每对不同整数 i<j，
// 把它们的最大公约数加起来，输出总和。
// 数据范围：2 ≤ n ≤ 2 × 10^6。
// 难度评分：1400（洛谷分级换算）
// 算法标签：欧拉函数、素数筛、数论

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e6+5;

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
    ans-=(n*(n+1))/2;
    ans/=2;
    cout<<ans<<endl;
    return 0;
}