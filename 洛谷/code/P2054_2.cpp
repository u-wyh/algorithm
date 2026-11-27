// https://www.luogu.com.cn/problem/P2054
// 题意：初始牌面按 1 到 N 排列。每次洗牌把牌均分成前后两半，再从后半开始交替取两半的首张牌，形成新顺序。求洗 M 次后第 L 张牌的牌面。
// 数据范围：N 为不超过 10^10 的正偶数，0 ≤ M ≤ 10^10，1 ≤ L ≤ N。
// 算法标签：快速幂、数论

#include<bits/stdc++.h>
using namespace std;
#define int long long

int n,m,l;

int mul(int a,int b,int mod){
    return (__int128)a*b%mod;
}

int power(int a,int b,int mod){
    int ans=1;
    while(b){
        if(b&1){
            ans=mul(a,ans,mod);
        }
        b>>=1;
        a=mul(a,a,mod);
    }
    return ans;
}

signed main()
{
    cin>>n>>m>>l;
    int mod=n+1;
    int inv2=(n+2)/2;
    int ans=mul(l,power(inv2,m,mod),mod);
    cout<<ans<<endl;
    return 0;
}