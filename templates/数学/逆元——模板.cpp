//这个文件中以下三种逆元：
//单个除数的逆元
//连续数字的逆元
//连续数字阶乘逆元
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n,m,mod;
int inv[MAXN];//连续数字的逆元
int fac[MAXN];//连续数字的阶乘
int facinv[MAXN];//连续数字阶乘的逆元

//乘法快速幂  求a的b次方对mod取余
long long power(long long a,long long b,long long mod){
    long long ans=1;
    while(b){
        if(b&1){
            ans*=a;
            ans%=mod;
        }
        b>>=1;
        a*=a;
        a%=mod;
    }
    return ans;
}

//单个除数的逆元
//费马小定理求(a/b)%mod的值
long long compute(long long a,long long b,long long mod){
    long long inv=power(b,mod-2,mod);//求b在%mod的情况下的逆元
    return (a*inv)%mod;
}

//连续数字的逆元
// 预计算模逆元
void build(int n) {
    inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        inv[i] = (mod - (long long)inv[mod % i] * (mod / i) % mod + mod) % mod;
    }
}

//连续数字阶乘的逆元
// 初始化阶乘表和逆元表
void build() {
    //先求出阶乘表
    fac[0] = 1; // 0! = 1
    for (int i = 1; i <= n; i++) {
        fac[i] = (fac[i - 1] * i) % mod;
    }

    // 利用线性递推优化计算逆元
    facinv[n] = power(fac[n], mod - 2,mod);//求出最后一个数字的阶乘逆元
    for (int i = n - 1; i >= 0; i--) {
        facinv[i] = (facinv[i + 1] * (i + 1)) % mod;//线性递推
    }
}

int main()
{
    cin>>n>>m>>mod;
    compute(n,m,mod);
    build(n);
    build();
    return 0;
}