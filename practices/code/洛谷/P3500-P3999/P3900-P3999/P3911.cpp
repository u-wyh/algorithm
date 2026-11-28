// https://www.luogu.com.cn/problem/P3911
// 题意：给定长度为 N 的正整数序列 A_1..A_N，
// 求 sum_{i=1}^N sum_{j=1}^N lcm(A_i, A_j)
// 的值。
// 数据范围：1 <= N <= 5 * 10^4，
// 1 <= A_i <= 5 * 10^4。
// 难度评分：1900（洛谷分级换算）
// 算法标签：莫比乌斯反演、线性筛
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;

int n;
int arr[MAXN];
int c[MAXN];
long long f[MAXN];
long long ans=0;

int mu[MAXN];
int cnt;
bool vis[MAXN];
int prime[MAXN];

void prepare(int n){
    mu[1] = 1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cnt] = i;
            mu[i] = -1;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            int p = prime[j];
            int num = i * p;
            vis[num]=true;
            
            if(i % p == 0){
                // p 是 i 的最小质因子
                mu[num] = 0;
                break;
            }
            else{
                // p 不是 i 的质因子
                mu[num] = -mu[i];
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j+=i){
            f[j]+=1ll*i*mu[i];
        }
    }
}

int main()
{
    prepare(MAXN-1);
    cin>>n;
    int m=0;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        m=max(arr[i],m);
        c[arr[i]]++;
    }
    n=m;
    for(int i=1;i<=n;i++){
        long long tmp=0;
        for(int j=1;j<=n/i;j++){
            tmp+=c[i*j]*j;
        }
        ans+=1ll*i*tmp*tmp*f[i];
    }
    cout<<ans<<endl;
    return 0;
}