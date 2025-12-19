//动态规划结合拓扑排序
// 有向图中最长路径
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 1e5+5;

int n,m;

int dp[MAXN];


int degree[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];

queue<int>q;

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        degree[v]++;
    }
    for(int i=0;i<n;i++){
        dp[i]=INT_MIN;
        if(degree[i]==0){
            q.push(i);
            dp[i]=0;
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            // int w=weight[i];
            dp[v]=max(dp[v],dp[u]+1);
            if(--degree[v]==0){
                q.push(v);
            }
        }
    }
    int ans=INT_MIN;
    for(int i=0;i<n;i++){
        cout<<dp[i]<<' ';
    }
    cout<<endl;
    for(int i=0;i<n;i++){
        ans=max(ans,dp[i]);
    }
    cout<<ans<<endl;
    return 0;
}

/*
7 11
0 1 8
0 3 4
0 4 5
1 2 3
2 6 6
3 4 1
4 1 2
4 2 7
4 5 2
5 2 3
5 6 9
*/