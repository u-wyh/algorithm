// https://www.luogu.com.cn/problem/P1370
// 题意：给整数数组 a。
// 对每个非空连续区间 [l,r]，统计该区间按原顺序抽取能得到多少种不同的值序列，空序列也算，相同值序列去重。
// 把所有区间的计数相加，对 998244353 取模。
// 数据范围：1 ≤ n ≤ 10^5，a[i] 的绝对值不超过 10^9。

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MOD = 998244353;

int n;
int nums[MAXN];
map<int,int>pos;
long long dp[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    dp[n+1]=0;
    for(int i=n;i>=1;i--){
        dp[i]=(dp[i+1]*2+2)%MOD;
        int k=pos[nums[i]];
        if(k!=0){
            dp[i]=(dp[i]-dp[k+1]-1)%MOD;
        }
        pos[nums[i]]=i;
    }
    long long ans=0;
    for(int i=1;i<=n;i++){
        ans=(ans+dp[i])%MOD;
    }
    cout<<ans<<endl;
    return 0;
}