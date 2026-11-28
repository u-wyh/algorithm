// https://atcoder.jp/contests/arc145/tasks/arc145_c
// 题意：给定 N，考虑 1 到 2N 的所有排列。
// 将一个排列按原顺序分成两个长为 N 的子序列 A、B。
// 该排列的得分是各分法中对应项乘积之和的最大值。
// 输出：达到最高得分的排列数，对 998244353 取模。
// 数据范围：1 <= N <= 2*10^5。
// 难度评分：1900（AtCoder Problems 换算）
// 算法标签：组合计数、卡特兰数
#include<bits/stdc++.h>
using namespace std;
const int MOD = 998244353;

int main()
{
    int n;
    cin>>n;
    if(n==1){
        cout<<2<<endl;
        return 0;
    }
    long long ans=1;
    for(int i=n+2;i<=2*n;i++){
        ans*=i;
        ans%=MOD;
    }
    for(int i=1;i<=n;i++){
        ans*=2;
        ans%=MOD;
    }
    cout<<ans<<endl;
    return 0;
}