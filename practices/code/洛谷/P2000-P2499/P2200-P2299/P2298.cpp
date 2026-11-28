// https://www.luogu.com.cn/problem/P2298
// 题意：n*m 网格（m 起点，d 终点，# 障碍，. 空地），
// 每步上下左右移动一格。
// 求从起点到终点的最少步数，无解输出 No Way!。
// 数据范围：3 <= n, m <= 2000。
// 难度评分：1300（洛谷分级换算）
// 算法标签：广度优先搜索
#include<bits/stdc++.h>
using namespace std;
#define MAX 2005

int n,m,n1,m1,n2,m2;
int nums[MAX][MAX],d[MAX][MAX];
char s[MAX];
struct coord{
    int x,y;
};
queue<coord>Q;
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

int main()
{
    memset(d,-1,sizeof(d));
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>s[j];
            if(s[j]=='#'){
                nums[i][j]=0;
            }else{
                nums[i][j]=1;
                if(s[j]=='m'){
                    n1=i,m1=j;
                }
                if(s[j]=='d'){
                    n2=i,m2=j;
                }
            }
        }
    }
    Q.push({n1,m1});
    d[n1][m1]=0;
    while(!Q.empty()){
        coord u=Q.front();
        Q.pop();
        int ux=u.x,uy=u.y;
        for(int k=0;k<4;k++){
            int x=ux+walk[k][0],y=uy+walk[k][1];
            if(x==0||x>n||y>m||y==0||d[x][y]!=-1||nums[x][y]==0){
                continue;
            }
            d[x][y]=d[ux][uy]+1;
            Q.push({x,y});
            if(x==n2&&y==m2){
                printf("%d\n",d[x][y]);
                return 0;
            }
        }
    }
    printf("No Way!\n");
    return 0;
}
