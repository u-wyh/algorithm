// https://www.luogu.com.cn/problem/P9823
// 题意：给定 n, k，求有多少个 1..n 的排列 a_1..a_n 满足：
// 对所有 k < i <= n
// 均有 a_i > min{a_{i-k}, ..., a_{i-1}}。
// 结果对 998244353 取模。
// 题意：一行输入 n, k；输出一行一个整数。
// 数据范围：1 <= k <= 10^7，1 <= n <= 10^7。
// 难度评分：1800（洛谷分级换算）
// 算法标签：组合数学、动态规划
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 1e7+5;


int n,k;
int fac[MAXN];
int inv[MAXN];

int f[MAXN];
int g[MAXN];

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(a*ans)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

void prepare(int n){
    inv[0]=1;
    fac[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=(fac[i-1]*i)%MOD;
    }
    inv[n]=power(fac[n],MOD-2);
    for(int i=n-1;i>=1;i--){
        inv[i]=(inv[i+1]*(i+1))%MOD;
    }
}

signed main()
{
    cin>>n>>k;
    prepare(n);
    if(n<=k){
        cout<<fac[n]<<endl;
        return 0;
    }
    for(int i=1;i<=k;i++){
        f[i]=fac[i];
    }
    f[0]=g[0]=1;
    for(int i=1;i<=n;i++){
        f[i]=g[i-1];
        if(i-1-k>=0){
            f[i]=(f[i]-g[i-k-1]+MOD)%MOD;
        }
        f[i]=(f[i]*fac[i-1])%MOD;
        g[i]=(g[i-1]+f[i]*inv[i]%MOD)%MOD;
    }
    cout<<f[n]<<endl;
    return 0;
}