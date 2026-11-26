// https://www.luogu.com.cn/problem/P1941
// 题意：小鸟从最左边任意整数高度出发，每秒向右一格。
// 点按则按次数累加上升且封顶于 m，不按则下降。
// 高度必须为正，经过管道时必须严格在开口内。
// 能通关则输出 1 和最少点按次数，否则输出 0 和最多通过的管道数。
// 数据范围：5 ≤ n ≤ 10000，5 ≤ m ≤ 1000，0 ≤ k < n，0 < x,y < m，0 < p < n，0 ≤ l < h ≤ m
// l+1 < h，管道位置互异。

#include<bits/stdc++.h>
using namespace std;
const int NA = INT_MAX;

int n,m,t;
struct node{
    int up,down;
    int low,high;
}nums[10005];
int dp[10005][1005];

bool check(int i,int j){
    if(j<0||j>m){
        return false;
    }
    if(dp[i][j]==NA){
        return false;
    }
    return true;
}

int main()
{
    cin>>n>>m>>t;
    for(int i=0;i<n;i++){
        cin>>nums[i].up>>nums[i].down;
        nums[i].low=0,nums[i].high=m;
    }
    for(int i=1;i<=t;i++){
        int u,high,low;
        cin>>u>>low>>high;
        nums[u].low=low;
        nums[u].high=high;
    }
//    for(int i=0;i<n;i++){
//        cout<<i<<' '<<nums[i].low<<' '<<nums[i].high<<' '<<nums[i].down<<' '<<nums[i].up<<endl;
//    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            dp[i][j]=NA;
        }
    }
    int obs=0;
    for(int i=1;i<=n;i++){
        int flag=1;
        //cout<<i<<' '<<obs<<endl;
        if(nums[i].low!=0||nums[i].high!=m){
            obs++;
        }
        for(int j=nums[i].low;j<=nums[i].high;j++){
            if(check(i-1,j+nums[i-1].down)){
                flag=0;
                dp[i][j]=min(dp[i][j],dp[i-1][j+nums[i-1].down]);
            }
            for(int k=1;k*nums[i-1].up<=j;k++){
                if(check(i-1,j-k*nums[i-1].up)){
                    flag=0;
                    dp[i][j]=min(dp[i][j],dp[i-1][j-k*nums[i-1].up]+k);
                }
            }
            if(j==m){
                for(int k=m-nums[i-1].up;k<=m;k++){
                    //cout<<i<<' '<<m<<' '<<k<<endl;
                    if(dp[i-1][k]!=NA){
                        flag=0;
                        //cout<<' '<<i<<endl;
                        dp[i][m]=min(dp[i][m],dp[i-1][k]+1);
                    }
                }
            }
        }
        if(flag){
            //cout<<' '<<i<<' ';
            cout<<0<<endl<<obs<<endl;
            return 0;
        }
    }
    cout<<1<<endl;
    int ans=NA;
    for(int i=0;i<=m;i++){
        ans=min(ans,dp[n][i]);
    }
    cout<<ans<<endl;
    return 0;
}
