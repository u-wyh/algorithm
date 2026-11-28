// https://www.luogu.com.cn/problem/P2261
// 题意：给定正整数 n 和 k，求 sum_{i=1..n} (k mod i)。
// 输出计算结果。
// 数据范围：1 <= n, k <= 10^9。
// 难度评分：1700（洛谷分级换算）
// 算法标签：整除分块
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n,k;
int ans;

signed main()
{
    cin>>n>>k;
    ans=n*k;
    int l=1,r;
    while(l<=min(n,k)){
        int t=k/l;
        // r=min(n,n/t);
        r=min(k/t,n);
        ans-=t*(l+r)*(r-l+1)/2;
        l=r+1;
    }
    cout<<ans<<endl;
    return 0;
}