// https://www.luogu.com.cn/problem/P2303
// 题意：给定整数 n，求 sum_{i=1..n} gcd(i, n)。
// 输出计算结果。
// 数据范围：1 <= n < 2^32。
// 难度评分：1700（洛谷分级换算）
// 算法标签：欧拉函数、数论
#include<bits/stdc++.h>
using namespace std;
#define int long long

int phi(int n){
    int ans=n;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            ans=ans/i*(i-1);
            while(n%i==0){
                n/=i;
            }
        }
    }
    if(n>1){
        ans=ans/n*(n-1);
    }
    return ans;
}

signed main()
{
    int n;
    cin>>n;
    int ans=0;
    for(int i=1;i*i<=n;i++){
        if(n%i==0){
            ans+=i*phi(n/i);
            if(i*i!=n){
                ans+=phi(i)*n/i;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}