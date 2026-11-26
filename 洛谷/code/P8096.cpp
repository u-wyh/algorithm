// https://www.luogu.com.cn/problem/P8096
// 题意：N 头奶牛排成一行，第 i 头牛饥饿度上限为 H_i（即 h_i ∈ [0, H_i]∩Z）。
// 每次操作可选择相邻两头牛 i 和 i+1 各使饥饿度减 1。
// 求有多少个符合上界的非负整数元组 [h_1, ..., h_N]，能够通过若干次操作使所有奶牛的饥饿度变成同一个非负整数，答案对 10^9 + 7 取模。
// 第一行输入 N，第二行输入 H_1..H_N。
// 输出一行一个整数。
// 数据范围：1 <= N <= 100，0 <= H_i <= 1000。
#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;

int n,maxx=0;
int h[105];
int tmp[105];
int dp[105][1005];



int main()
{
    cin>>n;
    int k=INT_MAX;
    for(int i=1;i<=n;i++){
        cin>>h[i];
        k=min(h[i],k);
        maxx=max(maxx,h[i]);
    }
    if(n%2==0){
        k=0;
    }
    for(int i=0;i<=k;i++){
        for(int j=0;j<n;j++){
            for(int p=0;p<=maxx;p++){
                dp[j][p]=0;
            }
        }
        for(int j=1;j<=n;j++){
            tmp[j]=h[j]-i;
        }
        dp[1][tmp[1]]=1;
        
    }
    return 0;
}