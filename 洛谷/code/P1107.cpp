// https://www.luogu.com.cn/problem/P1107
// 题意：有 N 棵高度为 H 的树，第 i 棵树在给定高度长着若干柿子。
// 小猫可从顶端开始，同树下降一格，或跳到另一棵树并下降 Delta 格，到地面结束。
// 经过某处可以吃掉那里的柿子，求最多能吃几个。
// 数据范围：1 ≤ N,H ≤ 2000，1 ≤ Delta ≤ H，每棵树至多 5000 个柿子，柿子的高度在 [1,H]。

#include<bits/stdc++.h>
using namespace std;

int n,h,delta;
int nums[2005][2005];
int dp[2005][2005];
int maxans[2005];

int main()
{
    cin>>n>>h>>delta;
    for(int i=1;i<=n;i++){
        int k;
        cin>>k;
        for(int j=1;j<=k;j++){
            int a;
            cin>>a;
            nums[i][a]++;
        }
    }
    for(int j=1;j<=h;j++){
        for(int i=1;i<=n;i++){
            dp[i][j]=max(dp[i][j-1],maxans[(j-delta)>0?(j-delta):0])+nums[i][j];
            maxans[j]=max(maxans[j],dp[i][j]);
        }
    }
    cout<<maxans[h];
    return 0;
}
