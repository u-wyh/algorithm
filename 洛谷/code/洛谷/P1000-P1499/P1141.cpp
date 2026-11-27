// https://www.luogu.com.cn/problem/P1141
// 题意：给一个 n × n 的 01 迷宫。
// 从一个格子出发，每步可走到上下左右相邻且数字不同的格子。
// 给 m 次询问，每次输入起点 (i, j)，输出能到达的不同格子数，起点也算。
// 数据范围：1 ≤ n ≤ 1000，1 ≤ m ≤ 10^5，
// 1 ≤ i, j ≤ n。
// 算法标签：深度优先搜索、记忆化搜索

#include<bits/stdc++.h>
using namespace std;

int n,m,ans[100002],x,y,f[1002][1002];
char s[1002][1002];

void dfs(int r,int c,int z,int lll){
    if (r<0 || r>=n || c<0 || c>=n || f[r][c]!=-1 || s[r][c]-'0'!=z)
        return;
    f[r][c]=lll;
    ans[lll]++;
    dfs(r-1,c,!z,lll);
    dfs(r+1,c,!z,lll);
    dfs(r,c-1,!z,lll);
    dfs(r,c+1,!z,lll);
}

int main()
{
    scanf("%d%d",&n,&m);
    for (int i=0;i<n;i++)
    scanf("%s",s[i]);
    memset(f,-1,sizeof(f));
    for (int i=0;i<m;i++)
    {
        scanf("%d%d",&x,&y);
        x--;
        y--;
        if (f[x][y]==-1)
            dfs(x,y,s[x][y]-'0',i);
        else
            ans[i]=ans[f[x][y]];
    }
    for (int i=0;i<m;i++)
        printf("%d\n",ans[i]);
    return 0;
}
