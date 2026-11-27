// https://www.luogu.com.cn/problem/P2134
// 题意：共有 n 天假期，连续 x 天旅游花费 p*x*x 元，连续 x 天不旅游花费 q*x 元。
// 求度过这 n 天假期的最少花费。
// 输出最少花费。
// 数据范围：1 <= n <= 2*10^5，1 <= p <= q <= 10^4。
#include<bits/stdc++.h>
// 算法标签：枚举、贪心
using namespace std;

int n,p,q;
long long ans=LLONG_MAX;

long long compute(int a,int b){
    int x=a/b;
    int y=a%b;
    return 1ll*(b-y)*p*x*x+1ll*p*y*(x+1)*(x+1);
    //一定会有y次是x+1天连续的
}

int main()
{
    cin>>n>>p>>q;
    for(int i=0;i<=n;i++){
        ans=min(ans,1ll*i*q+compute(n-i,i+1));
    }
    cout<<ans<<endl;
    return 0;
}
