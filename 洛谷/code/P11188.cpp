#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int val[10];
string s;
int dp[MAXN][7];
int arr[MAXN];
int p[7]={1,10,100,1000,10000,100000,1000000};

signed main()
{
    int c,t;
    cin>>c>>t;
    while(t--){
        cin>>s;
        for(int i=1;i<=9;i++){
            cin>>val[i];
        }
        int sum=0;
        int n=s.length();
        dp[n+1][0]=dp[n+1][1]=dp[n+1][2]=dp[n+1][3]=dp[n+1][4]=dp[n+1][5]=dp[n+1][6]=0;//初始化
        for(int i=1;i<=n;i++){
            arr[i]=s[i-1]-'0';
            sum+=val[arr[i]];
            dp[i][0]=dp[i][1]=dp[i][2]=dp[i][3]=dp[i][4]=dp[i][5]=dp[i][6]=0;//初始化
        }
        for(int i=n;i>=1;i--){
            for(int j=1;j<=min(6ll,n-i+1);j++){
                dp[i][j]=max(dp[i+1][j],dp[i+1][j-1]+val[arr[i]]-arr[i]*p[j-1]);
            }
        }
        int ans=0;
        for(int i=0;i<=6;i++){
            ans=max(ans,dp[1][i]);
        }
        cout<<(sum-ans)<<endl;
    }
    return 0;
}
