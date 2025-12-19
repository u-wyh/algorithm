#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;

int n,m;
int sum[105][105];
int dp[105][105][105];

long long dfs(int x,int y,int len){
    //表示在第x行第y列长度为len的可能种类
    if(x==0){
        return 1;
    }
    int st=y-len+1;
    if(dp[x][y][len]){
        return dp[x][y][len];
    }
    long long ans=1;//表示直接结束
    for(int i=st;i<=y;i++){
        if(sum[x][i]){
            //首先不能是0
            for(int j=1;j<=min(sum[x][i],len-y+i);j++){
                ans+=dfs(x-1,i,j);
            }
        }
    }
    ans%=MOD;
    dp[x][y][len]=ans;
    return ans;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;
            cin>>c;
            if(c=='X'){
                sum[i][j]=0;
            }else{
                sum[i][j]=sum[i][j-1]+1;
            }
        }
    }
    long long ans=1;
    for(int i=1;i<=m;i++){
        if(sum[n][i]){
            for(int j=1;j<=sum[n][i];j++){
                ans+=dfs(n-1,i,j);
                ans%=MOD;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
