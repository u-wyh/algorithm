// https://www.luogu.com.cn/problem/P1535
// 题意：给一个有树障碍的草地网格和起终点。
// 每秒必须沿上下左右移动一格，不能停、出界或踩树。
// 统计恰好第 T 秒到达终点的路径数，中间可以重复经过格子。
// 数据范围：2 ≤ N,M ≤ 100，1 ≤ T ≤ 15，点号可走，星号是树。
// 难度评分：1300（洛谷分级换算）
// 算法标签：深度优先搜索

#include<bits/stdc++.h>
using namespace std;

int n,m,t;
char s[105];
int  nums[105][105];
int r1,c1,r2,c2;
int walk[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
int ans=0;

void dfs(int x,int y,int time){
    if(time>t)
        return ;
    if(time==t){
        if(x==r2&&y==c2){
            ans++;
            return ;
        }
        else{
            return ;
        }
    }
    for(int k=0;k<4;k++){
        int ux=x+walk[k][0],uy=y+walk[k][1];
        if(ux<=0||uy<=0||ux>n||uy>m||nums[ux][uy]==0)
            continue;
        dfs(ux,uy,time+1);
    }
}

int main()
{
    cin>>n>>m>>t;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>s[j];
            if(s[j]=='*')
                nums[i][j]=0;
            else
                nums[i][j]=1;
        }
    }
    cin>>r1>>c1>>r2>>c2;
    dfs(r1,c1,0);
    printf("%d\n",ans);
    return 0;
}
