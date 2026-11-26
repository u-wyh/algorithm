// https://www.luogu.com.cn/problem/P9611
// 题意：给定两个整数 N, M，求区间 [N, M] 内所有整数的因数个数之和。
// 题意：一行输入 N, M；输出一个整数。
// 数据范围：1 <= N <= M <= 10^12。
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
        ans+=(r-l+1)*k;
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