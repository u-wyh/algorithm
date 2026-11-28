// https://www.luogu.com.cn/problem/P9035
// 题意：T 组数据，求长度为 n 的正整数序列 a 的个数
// 满足 0 < a_1 <= a_2 <= ... <= a_n <= k
// 且对任意 i != j 有 a_i + a_j <= k + 1
// 答案对 10^9+7 取模。
// 数据范围：1 <= T <= 2*10^5，1 <= n, k <= 10^7。
// 难度评分：1800（洛谷分级换算）
// 算法标签：组合数学、快速幂、乘法逆元
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 2e7+5;

int fac[MAXN];
int inv[MAXN];

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

int comb(int a,int b){
    return fac[a]*inv[b]%MOD*inv[a-b]%MOD;
}

signed main()
{
    prepare(20000000);
    int T;
    cin>>T;
    while(T--){
        int n,k;
        cin>>n>>k;
        int ans;
        if(k%2){
            ans=(comb(n+(k+1)/2-1,(k+1)/2-1)+comb(n+k-(k+1)/2-1,n))%MOD;
        }
        else{
            ans=(comb(n+k/2-1,k/2-1)+comb(n+k/2-1,n))%MOD;
        }
        cout<<ans<<endl;
    }
    return 0;
}