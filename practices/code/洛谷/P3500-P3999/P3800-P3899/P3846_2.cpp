// https://www.luogu.com.cn/problem/P3846
// 题意：输入一行三个整数 p, b, n，其中 p 为质数。
// 求最小的非负整数 l，使得 b^l ≡ n (mod p)。
// 输出一行最小的 l；若无解输出 no solution。
// 数据范围：对于所有测试点，2 <= b < p < 2^31，p 为质数，
// 1 <= n < p。
// BSGS主要解决：给出 a、b、mod，
// 求满足 a^x=b (mod mod) 的最小非负整数x
// 如果有解，那么只需要考虑一个完整周期内的x，但是直接枚举x复杂度太高
// BSGS本质上是一种分块/根号分治思想
//
// 令 t=ceil(sqrt(mod))
// 把 x 写成：x=A*t-B
// 那么：
// a^(A*t-B)=b (mod mod)
// => a^(A*t)=b*a^B (mod mod)
//
// 先枚举B=0~t-1，把 b*a^B 的值记录到map中
// 再从小到大枚举A，计算 a^(A*t)
// 如果这个值在map中出现过，那么：
// x=A*t-B
//
// 对于同一个值，要记录最大的B，因为A确定时，B越大，x=A*t-B越小
// 整体复杂度 O(sqrt(mod) log(sqrt(mod)))
// 难度评分：1700（洛谷分级换算）
// 算法标签：BSGS、快速幂
#include<bits/stdc++.h>
using namespace std;
#define int long long

int p,a,b;

int power(int a,int b,int mod){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%mod;
        }
        b>>=1;
        a=(a*a)%mod;
    }
    return ans;
}

// 求解(a^x)%p=b的x最小取值是多少
// 要求gcd(a,p)=1 
int bsgs(int a,int b,int p){
    a%=p;
    b%=p;
    // 如果b为1  直接特判
    if(b==1){
        return 0;
    }
    map<int,int>mp;
    int t=ceil(sqrt((long double)p));

    // 枚举右边 b*a^B
    int now=b;
    for(int B=0;B<t;B++){
        // 保留最大的B
        mp[now]=B;
        now=(now*a)%p;
    }

    // 左边每次乘 a^t
    int at=power(a,t,p);
    now=1;
    // 枚举左边 a^(A*t)
    for(int A=0;A<=t;A++){
        if(mp.count(now)){
            int ans=A*t-mp[now];
            if(ans>=0){
                return ans;
            }
        }
        now=now*at%p;
    }

    return -1;
}

signed main()
{
    cin>>p>>a>>b;
    int ans=bsgs(a,b,p);
    if(ans==-1){
        cout<<"no solution"<<endl;
    }
    else{
        cout<<ans<<endl;
    }
    return 0;
}