// https://www.luogu.com.cn/problem/P2424
// 题意：f(X) 表示 X 的所有正约数之和，
// 给定正整数 X, Y (X < Y)。
// 求 f(X) + f(X+1) + ... + f(Y) 的值。
// 输出约数和的总和。
// 数据范围：1 <= X < Y <= 2*10^9。
// 难度评分：1700（洛谷分级换算）
// 算法标签：数论分块、前缀和
#include<bits/stdc++.h>
using namespace std;
#define int long long

int compute(int n){
    if(n<=0){
        return 0;
    }
    int l=1,r;
    int ans=0;
    while(l<=n){
        int k=n/l;
        r=n/k;
        ans+=(r-l+1)*(r+l)/2*k;
        l=r+1;
    }
    return ans;
}

signed main()
{
    int l,r;
    cin>>l>>r;
    cout<<(compute(r)-compute(l-1))<<endl;
    return 0;
}