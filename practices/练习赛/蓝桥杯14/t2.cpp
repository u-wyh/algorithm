#include<bits/stdc++.h>
using namespace std;

int ans=0;
int dp[31][101];

int dfs(int u,int now){
    if(u==31&&now==70){
        return 1;
    }
    if((30-u+1)*10+now<70){
        return 0;
    }
    if(now==100){
        return 0;
    }
    if(dp[u][now]){
        return dp[u][now];
    }
    int ans=0;
    if(now==70){
        ans++;
    }
    ans+=dfs(u+1,now+10);
    ans+=dfs(u+1,0);
    dp[u][now]=ans;
    return ans;
}

int main()
{
    cout<<dfs(1,0)<<endl;
    // cout<<ans<<endl;
    return 0;
}