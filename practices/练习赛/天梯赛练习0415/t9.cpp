#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m,q;

int vis[MAXN];
vector<int>vec[MAXN];

// int cnt=1;
// int head[MAXN];
// int nxt[MAXN];
// int to[MAXN];

// inline void addedge(int u,int v){
//     nxt[cnt]=head[u];
//     to[cnt]=v;
//     head[u]=cnt++;
// }

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); 
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int k;
        cin>>k;
        for(int j=1;j<=k;j++){
            int u;
            cin>>u;
            vec[u].push_back(i);
        }
    }
    cin>>q;
    for(int i=1;i<=q;i++){
        int u,v;
        cin>>u>>v;
        if(vec[u].size()>vec[v].size()){
            swap(u,v);
        }
        int ans=0;
        for(int j=0;j<(int)vec[u].size();j++){
            vis[vec[u][j]]=1;
        }
        for(int j=0;j<vec[v].size();j++){
            if(vis[vec[v][j]]){
                ans++;
            }
        }
        printf("%d\n",ans);
        for(int j=0;j<vec[u].size();j++){
            vis[vec[u][j]]=0;
        }
    }
    return 0;
}