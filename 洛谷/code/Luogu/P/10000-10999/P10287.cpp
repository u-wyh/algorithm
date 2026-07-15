#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

vector<int>nums[MAXN];
int n,m;
int arr[MAXN];
int indegree[MAXN];
queue<int>q;
int dp[MAXN][12];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        nums[u].push_back(v);
        indegree[v]++;
    }
    for(int i=1;i<=n;i++){
        if(indegree[i]==0){
            q.push(i);
        }
        dp[i][arr[i]]=1;
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=0;i<nums[u].size();i++){
            int v=nums[u][i];
            if(!--indegree[v]){
                q.push(v);
            }
            for(int i=1;i<=arr[v];i++){
                dp[v][arr[v]]=max(dp[v][arr[v]],dp[u][i]+1);
            }
            for(int i=1;i<=10;i++){
                dp[v][i]=max(dp[u][i],dp[v][i]);
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=10;j++){
            ans=max(ans,dp[i][j]);
        }
    }
    cout<<ans;
    return 0;
}
