#include<bits/stdc++.h>
using namespace std;
#define MAX 105

int n,x1,Y1,ans=0;
int nums[MAX][MAX],vis[MAX][MAX];

void dfs(int x,int y,int k){
    ans=max(ans,k);
    for(int i=1;x+i<=n;i++){
        if(vis[x+i][y]!=-1){
            if(i==1||nums[x+i][y]==1){
                break;
            }
            vis[x+i][y]=1;
            dfs(x+i,y,k+i);
            vis[x+i][y]=0;
            break;
        }
    }
    for(int i=1;x-i>=1;i++){
        if(vis[x-i][y]!=-1){
            if(i==1||vis[x-i][y]==1){
                break;
            }
            vis[x-i][y]=1;
            dfs(x-i,y,k+i);
            vis[x-i][y]=0;
            break;
        }
    }
    for(int i=1;y+i<=n;i++){
        if(vis[x][y+i]!=-1){
            if(i==1||vis[x][y+i]==1){
                break;
            }
            vis[x][y+i]=1;
            dfs(x,y+i,k+i);
            vis[x][y+i]=0;
            break;
        }
    }
    for(int i=1;y-i>=1;i++){
        if(vis[x][y-i]!=-1){
            if(i==1||vis[x][y-i]==1){
                break;
            }
            vis[x][y-i]=1;
            dfs(x,y-i,k+i);
            vis[x][y-i]=0;
            break;
        }
    }
}

int main()
{
    memset(vis,-1,sizeof(vis));
    cin>>n>>x1>>Y1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>nums[i][j];
            if(nums[i][j]==0)
                vis[i][j]=0;
        }
    }
    vis[x1][Y1]=1;
    dfs(x1,Y1,0);
    printf("%d\n",ans);
    return 0;
}

