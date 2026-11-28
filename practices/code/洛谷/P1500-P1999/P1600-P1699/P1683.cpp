// https://www.luogu.com.cn/problem/P1683
// 题意：给定 W 列 H 行的地图，从 @ 出发，可以向上下左右走到安全格 .，
// 不能踩 #。求能到达的不同格子数，包含起点。
// 数据范围：1 ≤ W,H ≤ 20。
// 难度评分：1000（洛谷分级换算）
// 算法标签：深度优先搜索、Flood Fill

#include<bits/stdc++.h>
using namespace std;
#define MAX 25

int n,m;
int nums[MAX][MAX],ans=0;
char s[MAX];

void dfs(int i, int j) {
    if (i == 0 || i > n || j == 0 || j > m || nums[i][j] != 1) {
        return;
    }
    nums[i][j] = 2;
    dfs(i - 1, j);
    dfs(i + 1, j);
    dfs(i, j - 1);
    dfs(i, j + 1);
}

int main()
{
    cin>>m>>n;
    int n1,m1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>s[j];
            if(s[j]=='#')
                nums[i][j]=0;
            else if(s[j]=='.')
                nums[i][j]=1;
            else{
                nums[i][j]=1;
                n1=i,m1=j;
            }
        }
    }
    dfs(n1,m1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(nums[i][j]==2)
                ans++;
        }
    }
    printf("%d",ans);
    return 0;
}
