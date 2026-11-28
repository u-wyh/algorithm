// https://www.luogu.com.cn/problem/P1913
// 题意：给定 n 行 m 列的方向网格。
// 每个格子都作为一个起点，按 u、d、l、r 指定的方向走，走到 o 算成功，
// 走出边界或一直循环都不算。
// 求成功的起点数。
// 数据范围：1 ≤ n,m ≤ 1000，地图只含 u、d、l、r、o。
// 难度评分：1000（洛谷分级换算）
// 算法标签：深度优先搜索

#include<bits/stdc++.h>
using namespace std;
#define MAX 1005

int n,m;
char s[MAX][MAX];
int d[MAX][MAX],ans=0;

void dfs(int u,int v){
    d[u][v]=1;
    if(s[u+1][v]=='u'&&u+1<=n){
        dfs(u+1,v);
    }
    if(s[u][v+1]=='l'&&v+1<=m){
        dfs(u,v+1);
    }
    if(s[u-1][v]=='d'&&u-1>=1){
        dfs(u-1,v);
    }
    if(s[u][v-1]=='r'&&v-1>=1){
        dfs(u,v-1);
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>s[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s[i][j]=='o'){
                dfs(i,j);
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(d[i][j]==1){
                ans++;
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
