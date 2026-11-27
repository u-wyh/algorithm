#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10;

int dp[MAXN][MAXN];
int ans[MAXN][MAXN];
string s1=" baababab";
string s2=" ababbabba";
int n=8;
int m=9;

void traceback(int i,int j){
    if(i==0||j==0){
        return ;
    }
    if(ans[i][j]==0){
        traceback(i-1,j-1);
        cout<<s1[i];
    }
    else if(ans[i][j]==1){
        traceback(i-1,j);
    }
    else{
        traceback(i,j-1);
    }
}

int main()
{
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s1[i]==s2[j]){
                dp[i][j]=dp[i-1][j-1]+1;
                ans[i][j]=0;
            }
            else{
                if(dp[i-1][j]>dp[i][j-1]){
                    dp[i][j]=dp[i-1][j];
                    ans[i][j]=1;
                }
                else{
                    dp[i][j]=dp[i][j-1];
                    ans[i][j]=2;
                }
            }
        }
    }
    cout<<dp[n][m]<<endl;
    traceback(n,m);
    return 0;
}