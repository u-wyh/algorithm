// https://www.luogu.com.cn/problem/P3935
// 题意：令 f(x) 为正整数 x 的正约数个数（若 x = prod p_i^{k_i}，则 f(x) = prod (k_i + 1)）。
// 给定 l 和 r，求 sum_{i=l}^r f(i) 对 998244353 取模的结果。
// 数据范围：1 <= l <= r <= 1.6 * 10^14（测试点 100 满足 1 <= l <= 10^14
// 1 <= r <= 1.6 * 10^14，r - l > 10^14）。
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int INV = (MOD+1)/2;

int x,y;

int solve(int n){
    if(n==0){
        return 0;
    }
    int ans=0;
    for(int lt=1,rt;lt<=n;lt=rt+1){
        int v=n/lt;
        rt=n/v;

        ans+=1ll*v*(rt-lt+1);
        ans%=MOD;
    }
    return ans;
}

signed main()
{
    cin>>x>>y;
    int ans=0;
    ans=solve(y);
    ans-=solve(x-1);
    ans=(ans%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}