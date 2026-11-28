// https://codeforces.com/problemset/problem/571/A
// 题意：三根木棍初始长 a, b, c，
// 可将总长至多 l 的非负整数长度分配给它们。
// 输出：能使三根木棍组成非退化三角形的分配方案数。
// 数据范围：1 <= a, b, c <= 3*10^5，
// 0 <= l <= 3*10^5。
// 难度评分：2100（CF 官方）
// 算法标签：容斥原理、组合数学
#include<bits/stdc++.h>
using namespace std;
#define int long long

int a,b,c,l;

int compute(int d){
    int ans=0;
    int st=max(0ll,d);
    for(int i=st;i<=l;i++){
        int res=l-i;
        int t=min(res,i-d);
        ans+=(t+1)*(t+2)/2;
    }
    return ans;
}

signed main()
{
    cin>>a>>b>>c>>l;
    int total=(l+3)*(l+2)*(l+1)/6;
    int bad=0;
    bad+=compute(b+c-a);
    bad+=compute(a+c-b);
    bad+=compute(a+b-c);
    total-=bad;
    cout<<total<<endl;
    return 0;
}