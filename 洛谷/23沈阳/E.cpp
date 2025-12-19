#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int INF = 1e9;

int n,m,p,q;
int dp[MAXN][MAXN][2];
bool vis[MAXN][MAXN][2];

struct node{
    int x,y,k;
};
queue<node>que;

void bfs(int x,int y,int k){
    if(vis[x][y][k]){
        return ;
    }
    // cout<<x<<' '<<y<<' '<<k<<' '<<dp[x][y][k]<<endl;
    vis[x][y][k]=true;
    if(k==1){
        int resx=n-x;
        int resy=m-y;
        for(int i=0;i<=min(resx,p);i++){
            for(int j=0;j<=min(resy,p-i);j++){
                if((((resx-i)==0)||(resx-i+q)>=(resy-j))&&(dp[x+i][y+j][0]>dp[x][y][1]+1)){
                    dp[x+i][y+j][0]=dp[x][y][1]+1;
                    que.push({x+i,y+j,0});
                }
            }
        }
    }
    else{
        for(int i=0;i<=min(x,p);i++){
            for(int j=0;j<=min(y,p-i);j++){
                if(((x-i)==0||(x-i+q)>=(y-j))&&(dp[x-i][y-j][1]>dp[x][y][0])){
                    dp[x-i][y-j][1]=dp[x][y][0]+1;
                    que.push({x-i,y-j,1});
                }
            }
        }
    }
}

int main()
{
    cin>>n>>m>>p>>q;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            dp[i][j][0]=INF;
            dp[i][j][1]=INF;
        }
    }
    dp[n][m][0]=0;
    que.push({n,m,0});
    while(!que.empty()){
        node tmp=que.front();
        que.pop();
        bfs(tmp.x,tmp.y,tmp.k);
    }
    int ans=INF;
    for(int i=0;i<=m;i++){
        ans=min(ans,min(dp[0][i][0],dp[0][i][1]));
    }
    if(ans==INF){
        ans=-1;
    }
    cout<<ans<<endl;
    return 0;
}