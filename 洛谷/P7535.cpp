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
