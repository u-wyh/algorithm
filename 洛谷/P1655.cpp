#include<bits/stdc++.h>
using namespace std;

int n,m;
int dp[105][105];

int main()
{
    for(int i=1;i<=100;i++){
        dp[i][1]=1;
    }
    for(int i=2;i<=100;i++){
        for(int j=1;j<=i;j++){
            dp[i][j]=(dp[i-1][j-1]+dp[i-1][j]*j);
        }
    }
    while(cin>>n>>m){
        cout<<dp[n][m]<<endl;
    }
    return 0;
}
