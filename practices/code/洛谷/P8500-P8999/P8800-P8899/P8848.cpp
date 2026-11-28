// https://www.luogu.com.cn/problem/P8848
// 题意：输入整数 n 和长度为 n 的序列 a（元素仅为 1 或 -1）；
// 统计有多少种不同的 a 的重排序列，
// 使得该序列的最大子段和达到所有重排中的最小值
// （两序列在任一位置不同即算不同，最大子段和至少包含 1 个元素）
// 输出对 998244353 取模的结果。
// 数据范围：1 <= n <= 10^4，a_i ∈ {1, -1}。
// 难度评分：1800（洛谷分级换算）
// 算法标签：动态规划、组合数学
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;

int n,m;
int dp[2][10005];

int compute(int n,int m){
    int ans=1;
    for(int i=1;i<=min(m,n-m);i++){
        ans*=(n-i+1);
        ans/=i;
        ans%=MOD;
    }
    return ans;
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int a;
        cin>>a;
        if(a==-1){
            m++;
        }
    }
    n=n-m;
    if(n<=m){
        cout<<compute(m+1,n)<<endl;
        return 0;
    }
    dp[0][0]=1;
    for(int i=1;i<=(m+n);i++){
        for(int j=0;j<=(n-m);j++){
            int op=i&1;
            if(j==0)
                dp[op][j]=dp[op^1][j+1]%MOD;
            else
                dp[op][j]=(dp[op^1][j-1]+dp[op^1][j+1])%MOD;
        }
    }
    cout<<dp[(n+m)&1][n-m]<<endl;
    return 0;
}
