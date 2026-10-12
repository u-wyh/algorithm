// 用途：求网格每格到最近 1 格的四联通距离。
// 时间：O(nm)。
// 空间：O(nm)。
// 注意：n、m<=100；无源点输出 -1。
#include<bits/stdc++.h>
using namespace std;

#define MAXN 101
#define MAXM 101

struct coord{
    int x,y;
};

int n,m;
// 全部值为 1 的格子同时入队，距离统一从 0 开始。
coord Q[MAXN*MAXM];
int ql,qr;
int ans[MAXN][MAXM],nums[MAXN][MAXM];
int walk[4][2]={{0,1},{0,-1},{1,0},{-1,0}};

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            ans[i][j]=-1;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&nums[i][j]);
            if(nums[i][j]==1){
                ans[i][j]=0;
                Q[qr++]={i,j};
            }
        }
    }
    while(ql<qr){
        coord u=Q[ql++];
        int ux=u.x,uy=u.y;
        for(int k=0;k<4;k++){
            int x=ux+walk[k][0],y=uy+walk[k][1];
            int d=ans[ux][uy];
            if(x<0||x>=n||y<0||y>=m||ans[x][y]!=-1)
                continue;
            ans[x][y]=d+1;
            Q[qr++]={x,y};
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%3d",ans[i][j]);
        }
        printf("\n");
    }
    return 0;
}
