#include<bits/stdc++.h>
using namespace std;

int n,m,p,x;
int dp[1005][1005];
int sum[1005][1005];
int a[1005][1005];

int main()
{
    cin>>n>>m>>p;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>x;
            sum[(n-j%n+i)%n+1][j]=x;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=2;j<=m;j++){
            sum[i][j]+=sum[i][j-1];
        }
    }
    for(int i=1;i<=n;i++){
        cin>>x;
        for(int j=1;j<=m;j++){
            a[(n-j%n+i)%n+1][j]=x;
        }
    }
    for(int i=1;i<=m;i++){
        for(int j=i;j<=m;j++){
            dp[i][j]=-1e9;
        }
    }
    for(int len=1;len<=m;len++){
        for(int i=1;i+len-1<=m;i++){
            int j=i+len-1;
            for(int k=i;k<j;k++){
                dp[i][j]=max(dp[i][j],dp[i][k]+dp[k+1][j]);
            }
            if(j-i>=p){
                continue;
            }
            for(int k=1;k<=n;k++){
                dp[i][j]=max(dp[i][j],sum[k][j]-sum[k][i-1]-a[k][i]);
            }
        }
    }
    cout<<dp[1][m]<<endl;
    return 0;
}
