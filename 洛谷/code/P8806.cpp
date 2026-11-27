// https://www.luogu.com.cn/problem/P8806
// 题意：输入 n 和 n 块砖的重量与价值 (w_i, v_i)；
// 从中选出若干块从下到上叠成一座塔，要求每块砖上方所有砖块的总重量不超过它自身的价值 v_i，输出能叠出的最大砖块总价值。
// 数据范围：1 <= n <= 1000，1 <= w_i <= 20，1 <= v_i <= 20000。
// 算法标签：背包动态规划、贪心、排序
#include<bits/stdc++.h>
using namespace std;

int n;
struct node{
    int w,v;
}arr[1005];
int dp[20010],ans;

bool cmp(node a,node b){
    return a.w+a.v<b.w+b.v;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i].w>>arr[i].v;
    }
    sort(arr+1,arr+n+1,cmp);
    for(int i=1;i<=n;i++){
        for(int j=arr[i].w+arr[i].v;j>=arr[i].w;j--){
            dp[j]=max(dp[j],dp[j-arr[i].w]+arr[i].v);
        }
    }
    for(int i=0;i<20009;i++){
        ans=max(ans,dp[i]);
    }
    cout<<ans<<endl;
    return 0;
}
