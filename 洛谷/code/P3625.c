// https://www.luogu.com.cn/problem/P3625
// 题意：输入矩阵行数 M、列数 N、正方形边长 K，以及 M*N 网格每个小块的石油储量（非负整数）。
// 选出 3 个互不相交的 K*K 正方形子区域，使这 3 个区域包含的所有小块石油储量总和最大。
// 输出最大总储量。
// 数据范围：K <= M, N <= 1500（保证至少存在 3 个互不相交的 K*K 正方形），每格储量为 [0, 500] 内整数。
#include<stdio.h>
#include<stdbool.h>

#define MAX 105

int n,m,nums[MAX][MAX];
bool vis[MAX][MAX];
char s[MAX][MAX];
int ans=0;

void dfs(int u,int v){
    if(u<1||u>n||v<1||v>m||nums[u][v]!=1||vis[u][v]==1)
        return ;
    if(u==n&&v==m){
        ans=1;
        return ;
    }
    vis[u][v]=1;
    dfs(u+1,v);
    dfs(u-1,v);
    dfs(u,v+1);
    dfs(u,v-1);
}

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
    dfs(1,1);
    if(ans!=0)
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}
