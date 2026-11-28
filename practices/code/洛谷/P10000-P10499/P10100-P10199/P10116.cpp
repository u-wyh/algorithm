// https://www.luogu.com.cn/problem/P10116
// 题意：长度 n 的数组起初全是 0。
// 每一步选一个位置并赋为 1 到 k 中的某个值，恰好做 q 步。
// 模式 B 的第 i 项由 (a×i+b) mod k + 1 生成。
// 对每一种操作序列，数最终数组里 B 连续出现了几次，
// 再把这些次数加起来对 998244353 取模。
// 数据范围：n,q,k ≤ 10^9，m ≤ 3 × 10^6 且 m ≤ n，
// 0 ≤ a,b ≤ 10^9。
// 难度评分：1800（洛谷分级换算）
// 算法标签：组合数学、快速幂

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 3e6+5;

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
    int n,m,q,k,a,b;
    cin>>n>>m>>q>>k>>a>>b;
    if(q<m){
        cout<<0<<endl;
        return 0;
    }
    prepare(m);
    int ans=0;
    int v=1;
    for(int i=0;i<=m;i++){
        ans=((ans+v*comb(m,i)*power(n-i,q))%MOD+MOD)%MOD;
        v*=-1;
    }
    ans=(ans*power(k,q-m))%MOD;
    ans=(ans*(n-m+1))%MOD;
    cout<<ans<<endl;
    return 0;
}