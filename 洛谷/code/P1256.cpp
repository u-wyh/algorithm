// https://www.luogu.com.cn/problem/P1256
// 题意：给定 N * M 的 01 矩阵（0 黑 1 白，保证至少有一个 1）。
// 题意：对每个像素点 (i, j)，求其到最近的白色像素点 (x, y) 的曼哈顿距离 |i-x|+|j-y|。
// 输入：第一行输入 N, M，接下来 N 行每行 M 个数字（0 或 1）。
// 输出：输出 N 行，每行 M 个空格隔开的整数表示对应位置的最短距离。
// 数据范围：1 <= N, M <= 182。
#include<bits/stdc++.h>
// 算法标签：广度优先搜索
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
