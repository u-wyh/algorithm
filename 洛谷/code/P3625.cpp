#include<bits/stdc++.h>
using namespace std;
#define MAX 100

struct coord{
    int x,y;
};

int n,m,nums[MAX][MAX];
char s[MAX][MAX];
int vis[MAX][MAX];
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
queue<coord>Q;

int main()
{
    scanf("%d %d",&n,&m);
    getchar();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%c",&s[i][j]);
            if(s[i][j]=='#')
                nums[i][j]=0;
            else if(s[i][j]=='.')
                nums[i][j]=1;
        }
        getchar();
    }
    Q.push({1,1});
    vis[1][1]=1;
    while(!Q.empty()){
        coord now=Q.front();
        Q.pop();
        for(int i=0;i<4;i++){
          int x=now.x+walk[i][0],y=now.y+walk[i][1];
          if(nums[x][y]==0||vis[x][y]==1)
                continue;
          Q.push({x,y});
          vis[x][y]=1;
        }
    }
    if(vis[n][m]!=0)
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}
