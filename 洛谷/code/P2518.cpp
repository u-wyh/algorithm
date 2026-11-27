// https://www.luogu.com.cn/problem/P2518
// 题意：给定正整数 n，可删去任意个 0（或不删）并将剩余数字任意重排（无前导 0）。
// 求能组成多少个不同的严格小于 n 的正整数。
// 输出方案数。
// 数据范围：n 的位数 <= 50，答案 <= 2^63-1。
#include<bits/stdc++.h>
// 算法标签：动态规划
using namespace std;
const int MAXN = 5e3+5;

int n;
int arr[MAXN];
int dp[MAXN];
int cnt[MAXN];
int ans1,ans2;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    for(int i=1;i<=n;i++){
        dp[i]=1;
        for(int j=1;j<i;j++){
            if(arr[j]>arr[i]){
                dp[i]=max(dp[i],dp[j]+1);
            }
        }
        ans1=max(ans1,dp[i]);
    }
    for(int i=1;i<=n;i++){
        if(dp[i]==1){
            cnt[i]=1;
        }
        for(int j=1;j<i;j++){
            if(arr[i]<arr[j]&&dp[j]+1==dp[i]){
                cnt[i]+=cnt[j];
            }
            if(arr[i]==arr[j]&&dp[j]==dp[i]){
                cnt[i]=0;
            }
        }
        if(dp[i]==ans1){
            ans2+=cnt[i];
        }
    }
    cout<<ans1<<' '<<ans2<<endl;
    return 0;
}
