#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int dp[1<<18][20],n,m,t1,t2,t3;
vector<int> to[20],co[20];
bool vis[1<<18][20];

int dfs(int now,int vis){
    if(now==n)
        return 0;
    if(dp[vis][now])
        return dp[vis][now];
    int len=-1<<25;
    for(int i=0;i<to[now].size();i++)
        if(!(vis&(1<<to[now][i]-1)))
            len=max(len,co[now][i]+dfs(to[now][i],vis|(1<<to[now][i]-1)));
    return dp[vis][now]=len;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>t1>>t2>>t3;
        to[t1+1].push_back(t2+1);
        co[t1+1].push_back(t3);
    }
    cout<<dfs(1,1);
    return 0;
}
