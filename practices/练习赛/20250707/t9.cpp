#include<bits/stdc++.h>
using namespace std;
const int MAXN = 305;

int n,m;
int val[MAXN];
int dp[MAXN][MAXN][MAXN];
vector<vector<int>>vec;

int f(int i,int j,int k){
    if(k==0){
        return 0;
    }
    if(j==0||k==1){
        return val[i];
    }
    if(dp[i][j][k]!=-1){
        return dp[i][j][k];
    }
    int ans=f(i,j-1,k);
    int v=vec[i][j-1];
    for(int t=1;t<k;t++){
        ans=max(ans,f(i,j-1,k-t)+f(v,vec[v].size(),t));
    }
    dp[i][j][k]=ans;
    return ans;
}

int main()
{
    cin>>n>>m;
    m++;
    vec.resize(n+1);
    for(int i=1;i<=n;i++){
        int u;
        cin>>u>>val[i];
        vec[u].push_back(i);
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            for(int k=0;k<=m;k++){
                dp[i][j][k]=-1;
            }
        }
    }
    cout<<f(0,vec[0].size(),m)<<endl;
    return 0;
}