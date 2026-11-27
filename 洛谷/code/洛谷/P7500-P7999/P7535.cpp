// https://www.luogu.com.cn/problem/P7535
// 题意：N 张面额为 c_i 的钞票，两人各选若干张使总面额相等且尽量大，
// 剩余钞票赌博翻倍后再平分，求每人最终分得的总金额。
// 数据范围：
// 1 <= N <= 500，c_i >= 1，sum c_i <= 10^5。
// 算法标签：动态规划、滚动数组
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;
const int MAXM = 2e5+5;

int n,sum;
int arr[MAXN];
int dp[MAXM];
int tmp[MAXM];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        sum+=arr[i];
    }
    for(int i=1;i<=sum;i++){
        dp[i]=INT_MIN;
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=sum;j++){
            tmp[j]=max(max(dp[abs(j-arr[i])],dp[j+arr[i]])+arr[i],dp[j]);
        }
        for(int j=0;j<=sum;j++){
            dp[j]=tmp[j];
        }
    }
    cout<<(sum-dp[0]/2)<<endl;
    return 0;
}
