#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2000;

int dp[20][20][MAXN][2];
int nums[20];
int len;

int dfs(int x,int pos,int now,int free){
    if(x==0){
        return now==0;
    }
    if(now<0){
        return 0;
    }
    if(dp[x][pos][now][free]!=-1){
        return dp[x][pos][now][free];
    }
    int up=free?9:nums[x];
    int ans=0;
    for(int i=0;i<=up;i++){
        ans+=dfs(x-1,pos,now+(x-pos)*i,free||i<nums[x]);
    }
    dp[x][pos][now][free]=ans;
    return ans;
}

int compute(int x){
    if(x<1){
        return 0;
    }
    int ans=0;
    len=0;
    while(x){
        nums[++len]=x%10;
        x/=10;
    }
    for(int i=1;i<=len;i++){
        for(int j=1;j<=len;j++){
            for(int k=0;k<2000;k++){
                dp[i][j][k][0]=-1;
                dp[i][j][k][1]=-1;
            }
        }
    }
    for(int i=1;i<=len;i++){
        ans+=dfs(len,i,0,0);
    }
    return ans-len;
}

signed main()
{
    int x,y;
    cin>>x>>y;
    int ans=compute(y)-compute(x-1);
    cout<<ans<<endl;
    return 0;
}