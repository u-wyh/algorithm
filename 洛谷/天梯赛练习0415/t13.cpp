#include<bits/stdc++.h>
using namespace std;

int n,m,k;
int arr[105][105];
int vis[105][105];
int stx,sty;
queue<pair<int,int>>q;
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

int ans[10005];
int ok[10005];

void bfs(){
    vis[stx][sty]=1;
    q.push({stx,sty});
    while(!q.empty()){
        int x=q.front().first;
        int y=q.front().second;
        q.pop();
        for(int i=0;i<4;i++){
            int nx=x+walk[i][0];
            int ny=y+walk[i][1];
            if(nx<=0||nx>n||ny<=0||ny>m||vis[nx][ny]||arr[nx][ny]==0){
                continue;
            }
            vis[nx][ny]=vis[x][y]+1;
            q.push({nx,ny});
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>arr[i][j];
            if(arr[i][j]==2){
                stx=i,sty=j;
            }
        }
    }
    bfs();
    cin>>k;
    for(int i=1;i<=k;i++){
        int u,v;
        cin>>u>>v;
        ans[vis[v][u]-1]++;
        ok[vis[v][u]-1]=i;
        // cout<<' '<<vis[v][u]<<endl;
    }
    for(int i=1;i<=10000;i++){
        if(ans[i]==1){
            cout<<ok[i]<<' '<<i<<endl;
            return 0;
        }
    }
    cout<<"No winner.";
    return 0;
}