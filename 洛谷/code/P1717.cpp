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
