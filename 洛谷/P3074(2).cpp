#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10005;
const int MAXM = 50005;

int n,m;
int Time[MAXN];
int u,v;
int ans=0;
int cost[MAXN];
int indegree[MAXN];
int cnt=1;
int head[MAXN];
int Next[MAXM];
int to[MAXM];
queue<int >q;

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>Time[i];
    }
    for(int i=1;i<=m;i++){
        cin>>u>>v;
        indegree[v]++;
        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;
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
        for(int i=head[cur];i>0;i=Next[i]){
            cost[to[i]]=max(cost[to[i]],cost[cur]);
            indegree[to[i]]--;
            if(indegree[to[i]]==0){
                q.push(to[i]);
            }
        }
    }
    cout<<ans;
    return 0;
}
