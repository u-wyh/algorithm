// https://www.luogu.com.cn/problem/P2802
// 题意：输入地图大小 n, m 以及 n 行 m 列的网格，包含障碍物(0)、空地(1)、起点(2)、家(3)、有鼠标的空地(4)。
// 起点满血 6 点，每次向四方向移动一格耗时 1 且扣 1 点血；血量降到 0 立刻死去（在家门口或鼠标格死去也算失败）。
// 走到格 4 且未死时瞬间将血量补满至 6 点（每次经过都能补满），不可静止、不可走障碍或出界。
// 输出一行一个整数，能安全回家输出最短时间，否则输出 -1。
// 数据范围：对于 100% 的数据，1 <= n, m <= 9。
#include<bits/stdc++.h>
using namespace std;

int n,m,n1,m1,n2,m2;
int nums[10][10];
int d1[10][10],d2[10][10];
struct coord{
    int x,y;
};
queue<coord>Q1;
queue<coord>Q2;
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

int main()
{
    cin>>n>>m;
    memset(d1,10000,sizeof(d1));
    memset(d2,10000,sizeof(d2));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&nums[i][j]);
            if(nums[i][j]==2){
                n1=i,m1=j;
            }
            if(nums[i][j]==3){
                n2=i,m2=j;
            }
        }
    }
    Q1.push({n1,m1});
    d1[n1][m1]=0;
    while(!Q1.empty()){
        coord u=Q1.front();
        Q1.pop();
        int ux=u.x,uy=u.y;
        for(int k=0;k<4;k++){
            int x=ux+walk[k][0],y=uy+walk[k][1];
            if(x<=0||x>n||y<=0||y>m||d1[x][y]!=10000||nums[x][y]==0)
                continue;
            d1[x][y]=d1[ux][uy]+1;
            Q1.push({x,y});
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(nums[i][j]==4){
                Q2.push({i,j});
                d2[i][j]=0;
            }
        }
    }
    while(!Q2.empty()){
        coord u=Q2.front();
        Q2.pop();
        int ux=u.x,uy=u.y;
        for(int k=0;k<4;k++){
            int x=ux+walk[k][0],y=uy+walk[k][1];
            if(x<=0||x>n||y<=0||y>m||d1[x][y]!=10000||nums[x][y]==0)
                continue;
            d2[x][y]=d2[ux][uy]+1;
            Q1.push({x,y});
        }
    }
    int ans=d1[n2][m2];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(nums[i][j]==4){
                ans=min(ans,d1[i][j]+d2[n2][m2]);
            }
        }
    }
    return 0;
}
