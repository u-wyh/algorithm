#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3005;

int n;
int val[MAXN];

int dp[MAXN];//false表示这个子树根后手必胜

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u,int fa){
    dp[u]=false;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs(v,u);
        if(dp[v]==false&&val[u]>val[v]){
            dp[u]=true;
        }
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        dfs(i,0);
        if(dp[i]){
            cout<<i<<' ';
        }
    }
    return 0;
}