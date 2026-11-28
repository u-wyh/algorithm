// https://www.luogu.com.cn/problem/P1596
// 题意：给田地地图，W 是水，点号是陆地。两个水格若上下、左右或斜角相邻就连通。
// 数出所有水格组成的连通块数。
// 数据范围：1 ≤ N,M ≤ 100，每行恰有 M 个地图字符。
// 难度评分：1000（洛谷分级换算）
// 算法标签：深度优先搜索、连通块

#include<stdio.h>
#define Max 105

int n,m;
int nums[Max][Max];

void dfs(int i, int j) {
    if (i < 0 || i == n || j < 0 || j == m || nums[i][j] != 1) {
        return;
    }
    nums[i][j] = 0;
    dfs(i - 1, j);
    dfs(i + 1, j);
    dfs(i, j - 1);
    dfs(i, j + 1);
    dfs(i - 1, j - 1);
    dfs(i + 1, j - 1);
    dfs(i - 1, j + 1);
    dfs(i + 1, j + 1);
}

int main()
{
    scanf("%d %d",&n,&m);
    getchar();
    char s[m];
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%c",&s[j]);
            if(s[j]=='W')
                nums[i][j]=1;
            else
                nums[i][j]=0;
        }
        getchar();
    }
    int islands = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (nums[i][j] == 1) {
                islands++;
                dfs(i, j);
            }
        }
    }
    printf("%d\n",islands);
    return 0;
}

