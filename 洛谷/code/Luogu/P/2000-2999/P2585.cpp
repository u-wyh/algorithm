#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int dp[MAXN][3];
int f[MAXN][3];
char s[MAXN];
int n,cnt;

void dfs(int i){
    if(s[i]=='0'){
        dp[i][0]=1;
        f[i][0]=1;
        return ;
    }
    if(s[i]=='1'){
        dfs(++cnt);
        dp[i][0]=1+max(dp[i+1][1],dp[i+1][2]);
        dp[i][1]=max(dp[i+1][0],dp[i+1][2]);
        dp[i][2]=max(dp[i+1][0],dp[i+1][1]);
        f[i][0]=1+min(f[i+1][1],f[i+1][2]);
        f[i][1]=min(f[i+1][0],f[i+1][2]);
        f[i][2]=min(f[i+1][0],f[i+1][1]);
    }
    else if(s[i]=='2'){
        dfs(++cnt);
        int k=++cnt;
        dfs(k);
        dp[i][0]=1+max(dp[i+1][1]+dp[k][2],dp[i+1][2]+dp[k][1]);
        dp[i][1]=max(dp[i+1][0]+dp[k][2],dp[i+1][2]+dp[k][0]);
        dp[i][2]=max(dp[i+1][0]+dp[k][1],dp[i+1][1]+dp[k][0]);

        f[i][0]=1+min(f[i+1][1]+f[k][2],f[i+1][2]+f[k][1]);
        f[i][1]=min(f[i+1][0]+f[k][2],f[i+1][2]+f[k][0]);
        f[i][2]=min(f[i+1][0]+f[k][1],f[i+1][1]+f[k][0]);
    }
}

int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    dfs(++cnt);
    cout<<max(max(dp[1][0],dp[1][1]),dp[1][2])<<' ';
    cout<<min(min(f[1][0],f[1][1]),f[1][2])<<endl;
    return 0;
}
