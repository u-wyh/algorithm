// https://www.luogu.com.cn/problem/P2568
// 题意：给定正整数 n，
// 求满足 1 <= x, y <= n
// 且 gcd(x,y) 为素数的数对 (x,y) 个数。
// 输出数对个数。
// 数据范围：1 <= n <= 10^7。
// 难度评分：1800（洛谷分级换算）
// 算法标签：欧拉函数、线性筛、前缀和
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e7+5;

long long phi[MAXN];
int prime[MAXN];
int cnt=0;
bool vis[MAXN];

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
}

int main()
{
    int n;
    cin>>n;
    euler(n);
    for(int i=1;i<=n;i++){
        phi[i]+=phi[i-1];
    }
    long long ans=0;
    for(int i=1;i<=cnt;i++){
        ans+=(2*phi[n/prime[i]]-1);
    }
    cout<<ans<<endl;
    return 0;
}