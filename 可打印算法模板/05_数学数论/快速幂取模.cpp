// 用途：计算 a 的 b 次方模 mod。
// 时间：O(log b)。
// 空间：O(1)。
// 注意：b>=0、mod>0；用 __int128 防止乘法溢出。
// 例题：https://www.luogu.com.cn/problem/P1226
// 题意：求 a 的 b 次方模 mod。
// 思路：按二进制拆指数，反复平方并在置位时累乘。
#include<bits/stdc++.h>
using namespace std;

// 按指数二进制位累乘；乘法用 __int128 取模。
long long power(long long a,long long b,long long mod){
    long long ans=1%mod;
    a%=mod;
    if(a<0) a+=mod;
    while(b>0){
        if(b&1){
            ans=(__int128)ans*a%mod;
        }
        a=(__int128)a*a%mod;
        b>>=1;//b向右移动一位
    }
    return ans;
}

int main()
{
    long long a,b,mod;
    cin>>a>>b>>mod;
    cout<<a<<"^"<<b<< " mod "<<mod<<"="<<power(a,b,mod)<<endl;
    return 0;
}
