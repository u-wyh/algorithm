#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int cnt=1;
int head[MAXN];
int Next[MAXN<<1];
int weight[MAXN<<1];
int to[MAXN<<1];
int dis[MAXN];
bool vis[MAXN];

void dfs(int id,int val){
    dis[id]=val;
    vis[id]=true;
    for(int i=head[id];i>0;i=Next[i]){
        int v=to[i];
        if(!vis[v]){
            dfs(v,val^weight[i]);
        }
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;

        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        weight[cnt]=w;
        head[v]=cnt++;
    }
    dfs(1,0);
    cin>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        cout<<(dis[u]^dis[v])<<endl;
    }
    return 0;
}
