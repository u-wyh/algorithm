// https://www.luogu.com.cn/problem/P1999
// 题意：给定维数 a 和 b，统计 a 维超立方体有多少个 b 维面，
// 顶点和棱也分别作为 0 维和 1 维的面。答案对 10^9+7 取模。
// 数据范围：0 ≤ a,b ≤ 10^5，可能 b > a。
// 算法标签：组合数学、快速幂、逆元

#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;

long long power(long long a,int b){
    long long ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

int main()
{
    int a,b;
    cin>>a>>b;
    if(b>a){
        cout<<0;
        return 0;
    }
    if(a==b){
        cout<<1<<endl;
        return 0;
    }
    long long ans=power(2,a-b);
    long long tmp=1;
    for(int i=a-b+1;i<=a;i++){
        tmp=(tmp*i)%MOD;
    }
    ans=(ans*tmp)%MOD;
    tmp=1;
    for(int i=1;i<=b;i++){
        tmp=(tmp*i)%MOD;
    }
    ans=(ans*power(tmp,MOD-2)%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}