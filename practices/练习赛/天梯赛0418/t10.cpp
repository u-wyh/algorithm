#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;

int n,root;
int dep[MAXN];
int depth[MAXN];
bool in[MAXN];
int ans;
vector<int>vec[MAXN];

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    for(int i=0;i<(int)vec[u].size();i++){
        int v=vec[u][i];
        dfs(v,u);
        depth[u]=max(depth[u],depth[v]);
    }
    depth[u]=max(depth[u],dep[u]);
}

void dfs1(int u,int d){
    if(d==0){
        cout<<u;
    }
    else{
        cout<<' '<<u;
    }
    sort(vec[u].begin(),vec[u].end());
    for(int i=0;i<(int)vec[u].size();i++){
        int v=vec[u][i];
        if(depth[v]==ans){
            dfs1(v,d+1);
            break;
        }
    }
}

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        int k;
        cin>>k;
        for(int j=1;j<=k;j++){
            int v;
            cin>>v;
            vec[i].push_back(v);
            in[v]=1;
        }
    }
    for(int i=0;i<n;i++){
        if(!in[i]){
            root=i;
            dfs(i,n);
            ans=depth[i];
        }
    }
    // for(int i=0;i<n;i++){
    //     cout<<dep[i]<<' ';
    // }
    // cout<<endl;
    // for(int i=0;i<n;i++){
    //     cout<<depth[i]<<' ';
    // }
    // cout<<endl;
    cout<<ans<<endl;
    dfs1(root,0);
    return 0;
}