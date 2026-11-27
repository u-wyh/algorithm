// https://www.luogu.com.cn/problem/P3625
// 题意：输入矩阵行数 M、列数 N、正方形边长 K，
// 以及 M*N 网格每个小块的石油储量（非负整数）。
// 选出 3 个互不相交的 K*K 正方形子区域，
// 使这 3 个区域包含的所有小块石油储量总和最大。
// 输出最大总储量。
// 数据范围：
// K <= M,
// N <= 1500（保证至少存在 3 个互不相交的 K*K 正方形），
// 每格储量为 [0, 500] 内整数。
// 算法标签：广度优先搜索
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
