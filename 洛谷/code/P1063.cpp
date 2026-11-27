// https://www.luogu.com.cn/problem/P1063
// 题意：有 N 颗珠子围成一圈，每颗珠子的尾标记就是后一颗的头标记。
// 合并相邻两珠时，保留最外侧两个标记，释放这两个标记与中间共有标记的乘积。
// 求一直合并到只剩一颗时的最大总能量。
// 数据范围：4 ≤ N ≤ 100，头标记在 [1,1000]，答案不超过 2.1 × 10^9。
// 算法标签：区间动态规划

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;

int n,ans=0;
int arr[MAXN<<1];
int dp[MAXN<<1][MAXN<<1];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        arr[i+n]=arr[i];
    }
    for(int k=2;k<=n;k++){
        for(int i=1;i<=2*n-k;i++){
            for(int j=i;j<=i+k-2;j++){
                dp[i][i+k-1]=max(dp[i][i+k-1],dp[i][j]+dp[j+1][i+k-1]+arr[i]*arr[i+k]*arr[j+1]);
            }
        }
    }
    for(int i=1;i<=n;i++){
        ans=max(ans,dp[i][i+n-1]);
    }
    cout<<ans<<endl;
    return 0;
}
