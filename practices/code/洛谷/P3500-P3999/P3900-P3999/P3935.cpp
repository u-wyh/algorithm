// https://www.luogu.com.cn/problem/P3935
// 题意：令 f(x) 为正整数 x
// 的正约数个数
// （若 x = prod p_i^{k_i}，
// 则 f(x) = prod (k_i + 1)）。
// 给定 l 和 r，
// 求 sum_{i=l}^r f(i) 对 998244353 取模的结果。
// 数据范围：
// 1 <= l <= r <= 1.6 * 10^14
// （测试点 100 满足 1 <= l <= 10^14
// 1 <= r <= 1.6 * 10^14，r - l > 10^14）。
// 难度评分：2000（洛谷分级换算）
// 算法标签：数论分块
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;

int compute(int n){
    if(n<=0){
        return 0;
    }
    int l=1,r;
    int ans=0;
    while(l<=n){
        int k=n/l;
        r=n/k;
        ans+=(r-l+1)*k;
        ans%=MOD;
        l=r+1;
    }
    return ans;
}

signed main()
{
    int l,r;
    cin>>l>>r;
    int ans=compute(r)-compute(l-1);
    ans=(ans%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}