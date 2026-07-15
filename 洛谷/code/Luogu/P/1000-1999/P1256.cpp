#include<bits/stdc++.h>
using namespace std;

int n,m;
char s[185][185];
int nums[185][185],d[185][185];
struct coord{
    int x,y;
};
queue<coord>Q;
int walk[4][2]={{0,1},{0,-1},{1,0},{-1,0}};

int main()
{
    memset(d,-1,sizeof(d));
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>s[i][j];
            nums[i][j]=s[i][j]-'0';
            if(nums[i][j]==1){
                Q.push({i,j});
                d[i][j]=0;
            }
        }
    }
    while(!Q.empty()){
        coord u=Q.front();
        Q.pop();
        int ux=u.x,uy=u.y;
        for(int k=0;k<4;k++){
            int x=ux+walk[k][0],y=uy+walk[k][1];
            if(x>0 && x<=n && y>0 && y<=m &&nums[x][y]==0&&d[x][y]==-1){
                d[x][y]=d[ux][uy]+1;
                Q.push({x,y});
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            printf("%d ",d[i][j]);
        }
        printf("\n");
    }
    return 0;
}
