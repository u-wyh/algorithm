// https://www.luogu.com.cn/problem/P3848
// 题意：第一行输入棋盘边长 n 和起点坐标 (x, y)，接下来 n 行每行 n 个 0/1 数字表示棋盘。
// 跳棋规则：从当前 0 格沿上下左右 4 个方向连续越过至少 1 个 1 格落入下一个 0 格，跳过的距离为越过的 1 格数加 1；
// 每个 0 格及起点至多到达/经过一次（起点不可再到达或越过）。
// 输出能跳出的最大总距离；若不能跳则输出 0。
// 数据范围：题面输入格式给出 1 <= n <= 100（题目背景说明当前随机测试数据实际为 n <= 20）。
#include <bits/stdc++.h>
// 算法标签：深度优先搜索、回溯
using namespace std;

int n,i,j,k,ans;
int m[105][105],f[105][105];
int dx[4]={-1,1,0,0},dy[4]={0,0,1,-1};

void dfs(int x,int y,int step){
	int i;
	ans=max(ans,step);
    for(i=0;i<4;i++){
        int tx=x,ty=y,s=0;
        while(tx+dx[i]>0 && tx+dx[i]<=n && ty+dy[i]>0 && ty+dy[i]<=n){
			tx+=dx[i];
			ty+=dy[i];
			s++;
            if(m[tx][ty]==0) break;
        }
        if(tx>0 && tx<=n && ty>0 && ty<=n && f[tx][ty]==0 && m[tx][ty]==0 && s!=1) {
            f[tx][ty]=1;
            dfs(tx,ty,step+s);
            f[tx][ty]=0;
        }
    }
}

int main()
{
    int x,y,i,j;
	cin>>n>>x>>y;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            cin>>m[i][j];

    f[x][y]=1;
    dfs(x,y,0);
    cout<<ans<<endl;
    return 0;
}
