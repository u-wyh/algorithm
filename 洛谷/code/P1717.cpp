// https://www.luogu.com.cn/problem/P1717
// 题意：从 1 号鱼塘出发，只能往右走，总时间 H 小时。
// 经过相邻鱼塘耗时 5t_i 分钟。
// 在第 i 个鱼塘每钓 5 分钟收获一次，首次收获 f_i，此后每次减 d_i，最低为 0。
// 求最多能钓多少鱼。
// 数据范围：2 ≤ n ≤ 25，1 ≤ H ≤ 16，1 ≤ f_i ≤ 200，0 ≤ d_i ≤ 20，1 ≤ t_i ≤ 20。
// 算法标签：动态规划、分组背包

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 30;
const int MAXM = 220;//16*12

int n;
int m;
int nums[MAXN][MAXM];
struct node{
    int f,d;
    int limit;
}arr[MAXN];
int dp[MAXN][MAXM];
int t[MAXN];

int main()
{
    cin>>n>>m;
    m*=12;
    for(int i=1;i<=n;i++){
        cin>>arr[i].f;
    }
    for(int i=1;i<=n;i++){
        cin>>arr[i].d;
        if(arr[i].d!=0){
            arr[i].limit=(arr[i].f+arr[i].d-1)/arr[i].d;
        }else{
            arr[i].limit=m;
        }
        for(int j=1;j<=arr[i].limit;j++){
            nums[i][j]=nums[i][j-1]+arr[i].f-(j-1)*arr[i].d;
            printf("%5d",nums[i][j]);
        }
        cout<<endl;
    }
    for(int i=1;i<n;i++){
        cin>>t[i];
    }
    int T=0;
    for(int i=1;i<=n;i++){
        for(int j=T;j<=m;j++){
            dp[i][j]=dp[i-1][j-T];
            for(int k=1;k<=arr[i].limit&&j>=k+T;k++)
                dp[i][j]=max(dp[i][j],dp[i-1][j-k-T]+nums[i][k]);
        }
        T+=t[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            printf("%5d",dp[i][j]);
        }
        cout<<endl;
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        ans=max(ans,dp[i][m]);
    }
    cout<<ans;
    return 0;
}
