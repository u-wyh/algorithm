// https://www.luogu.com.cn/problem/P10780
// 题意：按给定八类食物的数量限制选恰好 n 件。
// 八类依次要求偶数、至多 1、至多 2、奇数、4 的倍数、至多 3、
// 至多 1、3 的倍数。
// 按每类数量区分方案，输出方案数对 10007 取模。
// 数据范围：1 ≤ n ≤ 10^500。
// 难度评分：1800（洛谷分级换算）
// 算法标签：组合数学、模运算

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e4+7;
const int INV = 1668;

int comb(int n){
    return (n*(n-1)/2)%MOD;
}

signed main()
{
    string s;
    cin>>s;
    int n=0;
    int len=s.length();
    for(int i=0;i<len;i++){
        n=(n*10+s[i]-'0')%MOD;
    }

    int ans=INV;
    ans=(ans*n)%MOD;
    ans=(ans*(n+1))%MOD;
    ans=(ans*(n+2))%MOD;
    cout<<ans<<endl;
    return 0;
}