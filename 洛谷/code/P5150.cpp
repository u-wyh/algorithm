// https://www.luogu.com.cn/problem/P5150
// 题意：给定正整数 n，求满足 lcm(a, b) = n 的有序正整数对 (a, b) 的方案总数。
// 数据范围：n <= 10^16。
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;

signed main()
{
    cin>>n;
    int ans=1;
    for(int i=2;i*i<=n;i++){
        if(n%i!=0){
            continue;
        }
        int res=2;
        int t=0;
        while(n%i==0){
            n/=i;
            t++;
        }
        res*=(t+1);
        res--;
        ans*=res;
    }
    if(n>1){
        ans*=3;
    }
    cout<<ans<<endl;
    return 0;
}