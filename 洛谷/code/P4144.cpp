// https://www.luogu.com.cn/problem/P4144
// 题意：第一行输入三个整数 n, b, p，第二行输入长度为 n 的初始序列 dirty_1..dirty_n。
// 设 x = max_{1<=l<=r<=n}
// ((dirty_l & ... & dirty_r) + (dirty_l | ... | dirty_r))。
// 输出 (x + 233)^b mod p。
// 数据范围：1 <= n, p <= 10^5，0 <= b, dirty_i <= 10^7。
#include<bits/stdc++.h>
// 算法标签：快速幂、贪心、数学
using namespace std;

int n,b,p,mod;

int ksm(int x,int k){
    int ans=1,base=x;
    while(k){
        if(k&1)
            ans=1ll*ans*base%mod;
        base=1ll*base*base%mod;
        k>>=1;
    }
    return ans;
}

int main()
{
    cin>>n>>b>>mod;
    for(int i=1,x;i<=n;i++) cin>>x,p=max(x,p);
    cout<<ksm(p*2+233,b)%mod;
}
