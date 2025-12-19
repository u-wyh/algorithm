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
