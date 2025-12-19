#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int MAXM = 100005;

int n,M,m;
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;
int indegree[MAXN];
int Time[MAXN];
int ans[MAXN];
queue<int >q;

int main()
{
    cin>>n>>M>>m;
    for(int i=1;i<=n;i++){
        cin>>Time[i];
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w;
        head[u]=cnt++;
        indegree[v]++;
    }
    for(int i=1;i<=n;i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int cur=q.front();
        ans[cur]=max(ans[cur],Time[cur]);
        q.pop();
        for(int i=head[cur];i>0;i=Next[i]){
            indegree[to[i]]--;
            if(indegree[to[i]]==0){
                q.push(to[i]);
            }
            ans[to[i]]=max(ans[cur]+weight[i],ans[to[i]]);
        }
    }
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
