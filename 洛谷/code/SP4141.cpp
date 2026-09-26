// https://www.luogu.com.cn/problem/SP4141
// 欧拉函数 phi(n)
//
// 用途：
// 求 1~n 中与 n 互质的整数个数
//
// 核心公式：
// phi(n) = n * Π(1 - 1/p)
// 其中 p 枚举 n 的所有不同质因子
//
// 使用方法：
// 对 n 分解质因数
// 每找到一个新的质因子 p：
// ans = ans / p * (p - 1)
//
// 注意：
// 每个质因子只需要处理一次
//
// 时间复杂度：O(sqrt(n))
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