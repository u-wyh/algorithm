// 用途：预处理模素数下的整数逆元、阶乘及阶乘逆元。
// 时间：预处理 O(n+log mod)，单次逆元查询 O(1)。
// 空间：O(n)。
// 注意：模数须为素数且 1≤n<mod、n≤300000；main 只演示预处理，不输出答案。
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
    return ((a % mod) * inv) % mod;
}

//连续数字的逆元
// 预计算模逆元
void build(int n) {
    inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        inv[i] = (mod - (long long)inv[mod % i] * (mod / i) % mod) % mod;
    }
}

//连续数字阶乘的逆元
// 初始化阶乘表和逆元表
void build() {
    //先求出阶乘表
    fac[0] = 1; // 0! = 1
    for (int i = 1; i <= n; i++) {
        fac[i] = (long long)fac[i - 1] * i % mod;
    }

    // 利用线性递推优化计算逆元
    facinv[n] = power(fac[n], mod - 2,mod);//求出最后一个数字的阶乘逆元
    for (int i = n - 1; i >= 0; i--) {
        facinv[i] = (long long)facinv[i + 1] * (i + 1) % mod;//线性递推
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
