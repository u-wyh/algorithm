#include<bits/stdc++.h>
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
