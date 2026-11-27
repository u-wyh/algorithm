// https://www.luogu.com.cn/problem/P1451
// 题意：给一个由数字 0 到 9 组成的矩形。
// 非零格子是细胞格，上下左右相邻的非零格可以连通。输出全部非零格组成的连通块数。
// 数据范围：1 ≤ n,m ≤ 100，每行由 m 个数字字符组成。
// 算法标签：深度优先搜索

#include<bits/stdc++.h>
using namespace std;
#define Max 1000

int n,m;
int nums[Max][Max];
char s[Max];

void dfs(int i, int j) {
    if (i < 0 || i == n || j < 0 || j == m || nums[i][j] ==0) {
        return;
    }
    // board[i][j] = '1'
    nums[i][j] = 0;
    dfs(i - 1, j);
    dfs(i + 1, j);
    dfs(i, j - 1);
    dfs(i, j + 1);
}

int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cin>>s[j];
            nums[i][j]=s[j]-'0';
        }
    }
    int islands = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (nums[i][j] != 0) {
                islands++;
                dfs(i, j);
            }
        }
    }
    printf("%d\n",islands);
    return 0;
}
