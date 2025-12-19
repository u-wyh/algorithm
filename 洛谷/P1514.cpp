#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;

int walk[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
int high[MAXN][MAXN];
bool vis[MAXN][MAXN];
int n,m;
int l[MAXN][MAXN],r[MAXN][MAXN];

void dfs(int x,int y){
    vis[x][y]=true;
    for(int i=0;i<4;i++){
        int nx=x+walk[i][0];
        int ny=y+walk[i][1];
        if(nx<1||nx>n||ny<1||ny>m){
            continue;
        }
        if (high[nx][ny]>=high[x][y])
            continue;
        if(!vis[nx][ny]){
            dfs(nx,ny);
        }
        l[x][y]=min(l[x][y],l[nx][ny]);
        r[x][y]=max(r[x][y],r[nx][ny]);
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>high[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            l[i][j]=INT_MAX;
        }
    }
    for(int i=1;i<=m;i++){
        l[n][i]=r[n][i]=i;
    }
    for(int i=1;i<=m;i++){
        if(!vis[1][i]){
            dfs(1,i);
        }
    }
    int cnt=0;
    for(int i=1;i<=m;i++){
        if(!vis[n][i]){
            cnt++;
        }
    }
    if(cnt){
        cout<<0<<endl<<cnt<<endl;
        return 0;
    }
    int left=1,right=0;
    while(left<=m){
        for(int i=1;i<=m;i++){
            if(l[1][i]<=left){
                right=max(right,r[1][i]);
            }
        }
        cnt++;
        left=right+1;
    }
    cout<<1<<endl<<cnt<<endl;
    return 0;
}
