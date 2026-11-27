// https://www.spoj.com/problems/ETF/
// 题意：T 组数据，每组给正整数 n。
// 输出：每组输出 1..n 中与 n 互质的整数个数。
// 数据范围：T <= 20000，1 <= n <= 10^6。
// 算法标签：欧拉函数、试除分解
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
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        cout<<phi(n)<<endl;
    }
    return 0;
}