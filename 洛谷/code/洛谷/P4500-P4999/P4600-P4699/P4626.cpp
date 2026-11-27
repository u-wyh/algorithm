// https://www.luogu.com.cn/problem/P4626
// 题意：给定正整数 n，
// 求能被 1 到 n 内所有整数整除的最小正整数（即 lcm(1..n)）对
// 100000007 取模的结果。
// 数据范围：n <= 10^8。
// 算法标签：线性筛、数论、快速幂
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e8+5;
const int MOD = 1e8+7;

int n;

int prime[MAXN];
int cnt=0;
bool vis[MAXN];

void euler(int n){
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cnt]=i;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=1;
            if(i%prime[j]==0){
                break;
            }
        }
    }
}

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans*=a;
        }
        b>>=1;
        a*=a;
    }
    return ans;
}

int main()
{
    cin>>n;
    euler(n);
    long long ans=1;
    double k=log(n);
    for(int i=1;i<=cnt;i++){
        ans=(ans*power(prime[i],(int)(k/log(prime[i]))))%MOD;
    }
    cout<<ans<<endl;
    return 0;
}