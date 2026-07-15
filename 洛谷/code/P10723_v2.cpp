#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int arr[MAXN];
int sz[MAXN];
int n;

void dfs1(int u,int f){
    sz[u]=arr[u];
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
            sz[u]+=sz[v];
        }
    }
}

int main()
{
    cin>>n;
    int root=0;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        if(arr[i]==1)
            root=i;
    }
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;
        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;
    }
    if(root==0){
        cout<<0;
        return 0;
    }
    dfs1(root,0);
    int ans=0;
    for(int i=1;i<=n;i++){
        if(arr[i]==0&&sz[i]!=0){
            ans++;
        }
    }
    cout<<ans;
    return 0;
}

