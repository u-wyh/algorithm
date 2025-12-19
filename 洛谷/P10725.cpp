#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int arr[MAXN];
int deep[MAXN];
int black,white,bdeep,wdeep;
int maxans;
int dist[MAXN];

void dfs(int u,int f){
    deep[u]=deep[f]+1;
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs(v,u);
        }
    }
}

void dfs1(int u,int f){
    dist[u]=dist[f]+1;
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
        }
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
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
    dfs(1,0);
    for(int i=1;i<=n;i++){
        if(arr[i]==0){
            if(deep[i]>bdeep){
                black=i;
                bdeep=deep[i];
            }
        }else{
            if(deep[i]>wdeep){
                white=i;
                wdeep=deep[i];
            }
        }
    }
    dist[0]=-1;
    dfs1(black,0);
    for(int i=1;i<=n;i++){
        if(arr[i]==1){
            maxans=max(maxans,dist[i]);
        }
    }
    fill(dist+1,dist+n+1,0);
    dfs1(white,0);
    for(int i=1;i<=n;i++){
        if(arr[i]==0){
            maxans=max(maxans,dist[i]);
        }
    }
    cout<<maxans;
    return 0;
}
