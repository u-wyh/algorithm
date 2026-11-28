// https://www.luogu.com.cn/problem/P2034
// 题意：从 n 个非负整数中选一些数，不能有超过 k 个连续位置都被选中，
// 求所选数的最大总和。
// 数据范围：1 ≤ k ≤ n ≤ 10^5，0 ≤ a_i ≤ 10^9。
// 难度评分：1600（洛谷分级换算）
// 算法标签：动态规划、单调队列

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int arr[MAXN];
int n,k;
long long sum=0;
long long dp[MAXN];
long long q[MAXN];

signed main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        sum+=arr[i];
    }
//    if(k==1){
//        cout<<0<<endl;
//        return 0;
//    }
    int head=0,tail=1;
    //cout<<q[head]<<endl;
    for(int i=1;i<=n;i++){
        dp[i]=dp[q[head]]+arr[i];
        while(head<tail&&dp[q[tail-1]]>=dp[i]){
            tail--;
        }
        q[tail++]=i;
        while(head<tail&&q[head]<i-k){
            //cout<<666<<endl;
            head++;
        }
        //cout<<i<<' '<<head<<' '<<q[head]<<' '<<tail<<' '<<q[tail]<<' '<<dp[i]<<endl;
    }
//    for(int i=1;i<=n;i++){
//        cout<<dp[i]<<' ';
//    }
//    cout<<endl;
    long long temp=LLONG_MAX;
    for(int i=n;i>=n-k;i--){
        temp=min(temp,dp[i]);
    }
    cout<<(sum-temp)<<endl;
    return 0;
}
/*
5 2
1
2
3
4
5
*/
