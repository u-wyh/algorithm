// https://www.luogu.com.cn/problem/P2012
// 题意：给定长度 n，用 12 种符号组成序列。
// 4 种符号出现次数各为奇数，另 4 种各为偶数，其余 4 种不限。
// 求合法序列数对 10^9 取模的值。
// 数据范围：至多 2×10^5 组，1 ≤ n < 2^63，读到 0 结束。
// 算法标签：快速幂、组合数学

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9;

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

signed main()
{
    int n;
    while(cin>>n&&n){
        if(n<4){
            cout<<0<<endl;
            continue;
        }

        int a=power(4,n-4);
        int b=power(3,n);
        int c=power(2,n);
        int ans=0;
        if((n&1)==0){
            ans=1;
        }
        else{
            ans=-1;
        }
        ans+=6;
        ans=(ans+b)%MOD;
        ans=(ans-4*c)%MOD;
        ans=(ans+MOD)%MOD;
        ans=(ans*a)%MOD;

        cout<<ans<<endl;
    }
    return 0;
}