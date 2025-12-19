#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
const int MAXM = 5000000;

int n,k,p,m;
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int Time[MAXN];
int cnt=1;
int indegree[MAXN];
int ans=0;
int cal=0;
queue<int> q;

int main()
{
    cin>>n>>k>>p;
    for(int i=1;i<=p;i++){
        int a;
        cin>>a;
        indegree[a]=0;
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        int u,k,w;
        cin>>u>>k;
        indegree[u]+=k;
        for(int j=1;j<=k;j++){
            cin>>w;
            Next[cnt]=head[w];
            to[cnt]=u;
            head[w]=cnt++;
        }
    }
    if(p+m<k){
        cout<<-1;
        return 0;
    }
    for(int i=1;i<=n;i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        ans=max(ans,Time[cur]);
        cal++;
        if(cal>=k){
            cout<<ans;
            return 0;
        }
        for(int i=head[cur];i>0;i=Next[i]){
            indegree[to[i]]--;
            if(indegree[to[i]]==0){
                q.push(to[i]);
            }
            Time[to[i]]=max(Time[cur]+1,Time[to[i]]);
        }
    }
    cout<<-1;
    return 0;
}

