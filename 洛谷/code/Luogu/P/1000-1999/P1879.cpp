#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e8;

int n,m;
int nums[13];
int ok[1<<12];
int cnt=1;
int dp[13][1<<12];

int dfs(int x,int s){
    if(x==n){
        return 1;
    }
    if(dp[x][s]!=-1){
        return dp[x][s];
    }
    int ans=0;
    for(int i=1;i<cnt;i++){
        if(((ok[i]&nums[x])==ok[i])&&(ok[i]&s)==0){
            //cout<<x<<' '<<ok[i]<<endl;
            ans=(ans+dfs(x+1,ok[i]))%MOD;
        }
    }
    dp[x][s]=ans;
    return ans;
}

int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            int k;
            cin>>k;
            if(k){
                nums[i]|=(1<<j);
            }
        }
        //cout<<nums[i]<<endl;
    }
    for(int i=0;i<(1<<m);i++){
        if((i&(i>>1))==0){
            ok[cnt++]=i;
            //cout<<i<<' ';
        }
    }
    //cout<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<(1<<m);j++){
            dp[i][j]=-1;
        }
    }
    int ans=0;
    for(int i=1;i<cnt;i++){
        if((nums[0]&ok[i])==ok[i]){
            //cout<<' '<<0<<' '<<ok[i]<<endl;
            ans=(ans+dfs(1,ok[i]))%MOD;
            //cout<<endl;
        }
    }
    cout<<ans;
    return 0;
}
