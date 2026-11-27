#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e5+5;

int n,m;
vector<int>vec[MAXN];
int val[MAXN];
map<int,int>vis[200005];
int fa[400005];

int dfs(int u,int v){
    int ans=1;
    for(int i=0;i<vec[u].size();i++){
        int to=vec[u][i];
        if(to==fa[u]){
            continue;
        }
        if(vis[v][val[to]]!=0){
            if(vis[v][val[to]]==fa[v]){
                continue;
            }
            ans=max(ans,1+dfs(to,vis[v][val[to]]));
        }
    }
    return ans;
}

void dfs1(int u,int f){
    fa[u]=f;
    for(int i=0;i<vec[u].size();i++){
        int v=vec[u][i];
        if(v==f){
            continue;
        }
        dfs1(v,u);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n+m;i++){
        cin>>val[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    for(int i=1;i<m;i++){
        int u,v;
        cin>>u>>v;
        u+=n,v+=n;
        vis[u][val[v]]=v;
        vis[v][val[u]]=u;
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    dfs1(n+1,0);
    dfs1(1,0);
    if(val[1]!=val[n+1]){
        cout<<0<<endl;
    }
    else{
        cout<<dfs(1,n+1)<<endl;
    }
    return 0;
}