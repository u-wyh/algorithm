#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXM = 105;

int n;
int place[505];//表示这个位置如果有监控  是几号监控
int look[MAXN][MAXM];
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=1;
int indegree[MAXN];
queue<int> q;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int x,m;
        cin>>x>>m;
        for(int j=1;j<=m;j++){
            cin>>look[i][j];
        }
        place[x]=i;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;look[i][j]!=0;j++){
            if(place[look[i][j]]!=0){
                Next[cnt]=head[i];
                to[cnt]=place[look[i][j]];
                head[i]=cnt++;
                indegree[place[look[i][j]]]++;
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(indegree[i]==0){
            q.push(i);
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
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(indegree[i]){
            ans++;
        }
    }
    if(ans!=0)
        cout<<ans;
    else
        cout<<"YES";
    return 0;
}
