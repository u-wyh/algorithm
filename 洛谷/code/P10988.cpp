#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

int nums[MAXN][MAXN];
bool vis[MAXN][MAXN];
int t[MAXN][MAXN];
queue<pair<int,int>>q;
int n;
int walk[2][2]={{1,0},{0,1}};

void bfs(){
    vis[1][1]=true;
    t[1][1]=1;
    q.push({1,1});
    while(!q.empty()){
        int ux=q.front().first;
        int uy=q.front().second;
        q.pop();
        if(vis[n][n]){
            t[n][n]-=1;
            cout<<t[n][n];
            return;
        }
        for(int i=0;i<2;i++){
            int x=ux+walk[i][0];
            int y=uy+walk[i][1];
            if(vis[x][y]||x>n||y>n||x<=0||y<=0){
                continue;
            }
            vis[x][y]=true;
            q.push({x,y});
            t[x][y]=t[ux][uy]+1;
        }
        for(int i=uy+1;i<=n;i++){
            if(nums[ux][i]>=nums[ux][i-1])
                break;
            if(vis[ux][i])
                continue;
            t[ux][i]=t[ux][uy]+1;
            vis[ux][i]=true;
            q.push({ux,i});
        }
        for(int i=uy-1;i>=1;i--){
            if(nums[ux][i]>=nums[ux][i+1])
                break;
            if(vis[ux][i])
                continue;
            t[ux][i]=t[ux][uy]+1;
            vis[ux][i]=true;
            q.push({ux,i});
        }
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>nums[i][j];
        }
    }
    bfs();
    return 0;
}
