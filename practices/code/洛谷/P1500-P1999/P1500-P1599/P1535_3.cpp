// https://www.luogu.com.cn/problem/P1535
// 题意：给一个有树障碍的草地网格和起终点。
// 每秒必须沿上下左右移动一格，不能停、出界或踩树。
// 统计恰好第 T 秒到达终点的路径数，中间可以重复经过格子。
// 数据范围：2 ≤ N,M ≤ 100，1 ≤ T ≤ 15，点号可走，星号是树。
// 难度评分：1300（洛谷分级换算）
// 算法标签：记忆化搜索、动态规划、剪枝

#include<bits/stdc++.h>
using namespace std;

int n,m,t;
char s[105];
int  nums[105][105];
int r1,c1,r2,c2;
int walk[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
int ans=0;

int re[108][108][20];
int dfs(int x,int y,int time)
{
	if(re[x][y][time]!=-1)
        return re[x][y][time];
	if(abs(x-r2)+abs(y-c2)>t-time)
        return re[x][y][time]=0;
	if(time>t)
        return re[x][y][time]=0;
	if(time==t)
	{
		if(x==r2&&y==c2)
            return re[x][y][time]=1;
		else
            return re[x][y][time]=0;
	}
	int ans=0;
	for(int k=0;k<4;k++){
        int ux=x+walk[k][0],uy=y+walk[k][1];
        if(ux<=0||uy<=0||ux>n||uy>m||nums[ux][uy]==0)
            continue;
        ans+=dfs(ux,uy,time+1);
    }
	return re[x][y][time]=ans;
}

int main()
{
    memset(re,-1,sizeof(re));
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
    //dfs(r1,c1,0);
    printf("%d\n",dfs(r1,c1,0));
    return 0;
}

