#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10005;
const int MAXM = 50005;

int n,m;
int Time[MAXN];
int cost[MAXN];
int indegree[MAXN];
int u,v;
int  ans=0;
vector<vector<int >>graph;
queue<int >q;

int main()
{
    cin>>n>>m;
    graph.resize(n+1);
    for(int i=1;i<=n;i++){
        cin>>Time[i];
    }
    for(int i=1;i<=m;i++){
        cin>>u>>v;
        graph[u].push_back(v);
        indegree[v]++;
    }
    for(int i=1;i<=n;i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        cost[cur]+=Time[cur];
        ans=max(ans,cost[cur]);
        for(int i=0;i<graph[cur].size();i++){
            indegree[graph[cur][i]]--;
            cost[graph[cur][i]]=max(cost[cur],cost[graph[cur][i]]);
            if(indegree[graph[cur][i]]==0){
                q.push(graph[cur][i]);
            }
        }
    }
    cout<<ans;
    return 0;
}
