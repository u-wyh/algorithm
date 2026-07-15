#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int MAXM = 200005;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int indegree[MAXN];
int ans[MAXN];
int cnt=1;
int n,m;
queue<int >q;

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;
        indegree[v]++;
    }
    for(int i=1;i<=n;i++){
        if(indegree[i]==0){
            q.push(i);
            //ans[i]=1;
        }
    }
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        for(int i=head[cur];i>0;i=Next[i]){
            indegree[to[i]]--;
            if(indegree[to[i]]==0){
                q.push(to[i]);
            }
            ans[to[i]]=max(ans[to[i]],ans[cur]+1);
        }
    }
    for(int i=1;i<=n;i++){
        printf("%d\n",ans[i]+1);
    }
    return 0;
}
