#include<bits/stdc++.h>
using namespace std;
const int MAXM = 105;

int nums[MAXM][MAXM];
int vis[MAXM][MAXM];
int t[MAXM][MAXM];
int n,m;
int ans=INT_MAX;
int walk[4][2]={{0,1},{0,-1},{1,0},{-1,0}};

void dfs(int x,int y,int k,int f){
    //表示到了xy  花费为k  f=1表示可用魔法
    if(k>=ans||k>t[x][y]){
        return;
    }
    t[x][y]=min(t[x][y],k);
    if(x==m&&y==m){
        ans=k;
        return;
    }
    for(int i=0;i<4;i++){
        int ux=x+walk[i][0];
        int uy=y+walk[i][1];
        if(vis[ux][uy]||ux>m||uy>m||ux<=0||uy<=0||(f==0&&nums[ux][uy]==0)){
            continue;
        }
        vis[ux][uy]=true;
        if(nums[ux][uy]==0){
            nums[ux][uy]=nums[x][y];
            dfs(ux,uy,k+2,0);
            nums[ux][uy]=0;
        }
        else if(nums[ux][uy]==nums[x][y]){
            dfs(ux,uy,k,1);
        }
        else if(nums[ux][uy]!=nums[x][y]){
            dfs(ux,uy,k+1,1);
        }
        vis[ux][uy]=false;
    }
}

int main()
{
    cin>>m>>n;
    for(int i=1;i<=n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        nums[u][v]=w+1;
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=m;j++){
            t[i][j]=INT_MAX;
        }
    }
    vis[1][1]=true;
    dfs(1,1,0,1);
    if(ans==INT_MAX)
        ans=-1;
    cout<<ans;
    return 0;
}
