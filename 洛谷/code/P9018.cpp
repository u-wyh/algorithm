// https://www.luogu.com.cn/problem/P9018
// 题意：数轴上 t=0 时从 x=0 出发，每秒向左(L)或向右(R)移动 1 单位，在 [0, N] 内移动并最终停在 x=0
// 且经过 i+0.5 (0 <= i < N) 的总次数恰好为 A_i。
// 求在改变方向次数（L/R 串相邻字符不同的次数）最少的前提下，有多少种不同的移动序列，对 10^9+7 取模。
// 数据范围：1 <= N <= 10^5，1 <= A_i <= 10^6（A_i 为正整数，各点经过次数合法）。
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;
const int MAXM = 1e5+5;
const int MOD = 1e9+7;

int n;
int fac[MAXN];
int inv[MAXN];

int nums[MAXM];

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
    prepare(500000);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        nums[i]/=2;
    }
    int ans=1;
    for(int i=1;i<n;i++){
        if(nums[i]>nums[i+1]){
            ans=(ans*comb(nums[i],nums[i+1]))%MOD;
        }
        else{
            ans=(ans*comb(nums[i+1]-1,nums[i]-1))%MOD;
        }
    }
    cout<<ans<<endl;
    return 0;
}