// https://www.luogu.com.cn/problem/P3004
// 题意：输入硬币数量 n，以及从左至右排列的每枚硬币价值 c_i。
// 小 A 先手，两人每回合只能从当前硬币序列的最左端或最右端取走一枚硬币并累加其价值，直至取空。
// 假设双方均采取使自己累计价值最大化的最优策略，求小 A 能获得的最大累计价值。
// 输出一行一个整数，表示小 A 的最大累计价值。
// 数据范围：对于 100% 的数据，1 <= n <= 5*10^3，1 <= c_i <= 5*10^3（空间限制 64 MiB）。
#include<bits/stdc++.h>
using namespace std;

int n;
int nums[5005];
int dp[5005];
int sum[5005];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        sum[i]=sum[i-1]+nums[i];
        dp[i]=nums[i];
    }
    for(int len=2;len<=n;len++){
        for(int i=1;i<=n-len+1;i++){
            int j=i+len-1;
            dp[i]=sum[j]-sum[i-1]-min(dp[i+1],dp[i]);
        }
    }
    cout<<dp[1]<<endl;
    return 0;
}

