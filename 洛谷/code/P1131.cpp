#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;
long dis[MAXN];//以i位头结点的子树  向下最深的距离
long ans=0;
int n,st;

void addedge(int u,int v,int w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dfs(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        int w=weight[i];
        if(v==f){
            continue;
        }
        dfs(v,u);
        dis[u]=max(dis[u],dis[v]+w);
    }
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        int w=weight[i];
        if(v==f){
            continue;
        }
        ans+=dis[u]-dis[v]-w;
    }
}

int main()
{
    cin>>n>>st;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dfs(st,0);
    cout<<ans;
    return 0;
}
