// https://www.luogu.com.cn/problem/P5389
// 题意：数列 a_i = 1+2+...+i（共 n 项），
// 以概率 a_i / sum_{j=1}^n a_j 独立选出两个元素 v1,
// v2
// 再分别在 [1, v1], [1, v2] 等概率选整数 a, b。
// 求 a > b 的概率对 998244353
// 取模的值（输入 n=0 表示 n 为正无穷）。
// 数据范围：
// 前 95% 数据 1 <= n <= 10^18
// 且 n, n+2 不为 998244353 倍数，最后 5% 数据 n=0。
// 难度评分：1800（洛谷分级换算）
// 算法标签：数学、快速幂
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;

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
    cin>>n;
    if(n==0){
        cout<<power(2,MOD-2)<<endl;
    }
    else{
        n%=MOD;
        int k=(n*n%MOD+2*n%MOD)%MOD;
        int ans=((k-3)*power(2*k%MOD,MOD-2))%MOD;
        ans=(ans+MOD)%MOD;
        cout<<ans<<endl;
    }
    return 0;
}