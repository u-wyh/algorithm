#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;

int n;
int val[MAXN][MAXN];
int dp[MAXN];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            cin>>val[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        dp[i]=INT_MAX;
    }
    dp[1]=0;
    for(int i=2;i<=n;i++){
        for(int j=1;j<i;j++){
            if(dp[j]!=INT_MAX){
                dp[i]=min(dp[i],dp[j]+val[j][i]);
            }
        }
    }
    cout<<dp[n]<<endl;
    return 0;
}
/*
3
5 15
7
*/