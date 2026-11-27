// https://www.luogu.com.cn/problem/P2979
// 题意：输入奶酪种类数 N、塔最大允许高度 T、大奶酪高度阈值 K，以及每种奶酪的价值 V_i 与原始高度 H_i（每种奶酪不限数量）。
// 若堆叠中某块奶酪上方存在至少一块原始高度 H >= K 的大奶酪，则该块奶酪的高度会被压低为原来的 4/5（仅计算一次压低）。
// 在总高度不超过 T 的前提下选择奶酪并决定堆叠顺序，使塔的总价值最大。
// 输出一行一个整数，表示奶酪塔的最大总价值。
// 数据范围：对于 100% 的数据，1 <= T <= 10^3，1 <= N <= 10^2，5 <= H_i <= T 且 5 | H_i
// 1 <= V_i <= 10^6，1 <= K <= T。
#include<bits/stdc++.h>
// 算法标签：动态规划、完全背包、枚举
using namespace std;

int n,m,K;
int dp[1005];
int cost[105],val[105];

int main()
{
    cin>>n>>m>>K;
    for(int i=1;i<=n;i++){
        cin>>val[i]>>cost[i];
    }
    for(int i=1;i<=n;i++){
        if(cost[i]>=K){
            continue;
        }
        for (int j = cost[i]; j <= m; j++) {
            dp[j] = max(dp[j], dp[j - cost[i]] + val[i]);
        }
    }
    int ans=0;
    ans=max(ans,dp[m]);
    for(int u=1;u<=n;u++){
        if(cost[u]>=K&&cost[u]<=m){
            for(int i=1;i<=m;i++){
                dp[i]=0;
            }
            for(int i=1;i<=n;i++){
                for (int j = cost[i]*4/5; j <= m-cost[u]; j++) {
                    dp[j] = max(dp[j], dp[j - cost[i]*4/5] + val[i]);
                }
            }
            ans=max(ans,dp[m-cost[u]]+val[u]);
        }
    }
    cout<<ans<<endl;
    return 0;
}
