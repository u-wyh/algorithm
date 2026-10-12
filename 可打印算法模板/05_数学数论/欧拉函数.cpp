// 用途：求 φ(n)，即 1 到 n 中与 n 互质的数目。
// 时间：O(√n)。
// 空间：O(1)。
// 注意：n>=1；单次 O(sqrt n)。
// 例题：https://www.luogu.com.cn/problem/SP4141
// 题意：求 1 到 n 中与 n 互质的整数个数。
// 思路：分解 n 的不同质因子，依次用 φ(n)=n∏(1-1/p) 更新。
#include<bits/stdc++.h>
using namespace std;
#define int long long

// 每个不同质因子 p 只更新一次 ans=ans/p*(p-1)。
int phi(int n){
    int ans=n;
    for(int i=2;i<=n/i;i++){
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
