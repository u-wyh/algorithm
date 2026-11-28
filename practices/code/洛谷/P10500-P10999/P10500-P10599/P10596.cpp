// https://www.luogu.com.cn/problem/P10596
// 题意：给正整数 N 和整数 K。
// 从 N 元素集合的所有子集中选至少一个子集。
// 各选中子集互不相同，交集大小须恰好为 K。
// 输出：合法方案数对 10^9+7 取模。
// 数据范围：1 <= N <= 10^6，0 <= K <= N。
// 难度评分：2000（洛谷分级换算）
// 算法标签：容斥原理、组合计数、快速幂
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int MOD = 1e9+7;

long long fac[MAXN];
long long inv[MAXN];
long long g[MAXN];
int n,k;

long long power(long long a,int b){
    long long ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        a=(a*a)%MOD;
        b>>=1;
    }
    return ans;
}

void build(){
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=(fac[i-1]*i)%MOD;
    }
    inv[n]=power(fac[n],MOD-2);
    for(int i=n-1;i>=1;i--){
        inv[i]=(inv[i+1]*(i+1))%MOD;
    }
}

long long comb(int n,int m){
    return (((fac[n]*inv[m])%MOD*inv[n-m])%MOD+MOD)%MOD;
}

long long compute(){
    build();
    long long tmp=2;
    for(int i=n;i>=0;i--){
        g[i]=tmp;
        tmp=(tmp*tmp)%MOD;
    }
    for(int i=0;i<=n;i++){
        g[i]=(g[i]+MOD-1)*comb(n,i)%MOD;
    }
    long long ans=0;
    for(int i=k;i<=n;i++){
        if((i-k)&1){
            ans=(ans+comb(i,k)*g[i]%MOD*(MOD-1)%MOD)%MOD;
        }
        else{
            ans=(ans+comb(i,k)*g[i]%MOD)%MOD;
        }
    }
    return ans;
}

int main()
{
    cin>>n>>k;
    cout<<compute()<<endl;
    return 0;
}