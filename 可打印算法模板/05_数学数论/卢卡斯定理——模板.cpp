// 用途：模数 p 为质数时，求 C(n+m,m) mod p；n、m 可以很大。
// 时间：O(p logₚ(n+m)+log p·logₚ(n+m))，每位的小组合数直接相乘。
// 空间：O(logₚ(n+m))，来自递归层数。
// 注意：p 必须是质数；输入给的是 n、m，所求组合数上标是 n+m。
// 例题：https://www.luogu.com.cn/problem/P3807
// 题意：每组输入 n、m、质数 p，求 C(n+m,m) mod p。
// 思路：按模 p 的每位拆成小组合数之积。
#include<bits/stdc++.h>
using namespace std;

long long n,m,p;

long long power(long long a,long long b){
    long long ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%p;
        }
        a=(a*a)%p;
        b>>=1;
    }
    return ans;
}

long long comb(long long n,long long m){
    // 处理一位 0≤n,m<p；分母用费马小定理求逆元。
    if(n<m){
        return 0;
    }
    m=min(m,n-m);
    long long a=1,b=1;
    for(int i=1;i<=m;i++){
        a=(a*(n-i+1))%p;
        b=(b*i)%p;
    }
    return a*power(b,p-2)%p;
}

long long lucas(long long n,long long m){
    // C(n,m) 按 p 进制逐位拆成小组合数的乘积。
    if(m==0){
        return 1;
    }
    else{
        return lucas(n/p,m/p)*comb(n%p,m%p)%p;
    }
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m>>p;
        cout<<lucas(n+m,m)<<endl;
    }
    return 0;
}
