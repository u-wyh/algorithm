#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2005;

char s1[MAXN];
char s2[MAXN];
int m,n,k;
int dp[MAXN][MAXN];

int main()
{
    cin>>s1>>s2>>k;
    n=strlen(s1);
    m=strlen(s2);
    //cout<<m<<n;
    for(int i=0;i<=n;i++){
        dp[i][0]=i*k;
    }
    for(int j=0;j<=m;j++){
        dp[0][j]=j*k;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            dp[i][j]=min(dp[i][j-1]+k,min(dp[i-1][j]+k,dp[i-1][j-1]+abs(int(s1[i-1]-s2[j-1]))));
        }
    }
    cout<<dp[n][m];
    return 0;
}
