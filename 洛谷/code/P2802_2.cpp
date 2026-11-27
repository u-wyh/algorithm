// https://www.luogu.com.cn/problem/P2802
// 题意：输入地图大小 n, m 以及 n 行 m 列的网格，包含障碍物(0)、空地(1)、起点(2)、家(3)、有鼠标的空地(4)。
// 起点满血 6 点，每次向四方向移动一格耗时 1 且扣 1 点血；血量降到 0 立刻死去（在家门口或鼠标格死去也算失败）。
// 走到格 4 且未死时瞬间将血量补满至 6 点（每次经过都能补满），不可静止、不可走障碍或出界。
// 输出一行一个整数，能安全回家输出最短时间，否则输出 -1。
// 数据范围：对于 100% 的数据，1 <= n, m <= 9。
#include<bits/stdc++.h>
// 算法标签：深度优先搜索、回溯、剪枝
using namespace std;

void dfs(int x,int y,int mou);
long long a[11][11],dir[4][2]={1,0,-1,0,0,1,0,-1};
int tx,ty,lx,ly,n,m,mou=6,times=0,minans=1<<30;

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
            if(a[i][j]==2){
                tx=i;ty=j;
                //记录开始点
            }
            if(a[i][j]==3){
                lx=i;ly=j;
                //记录结束点
            }
        }
    dfs(tx,ty,mou);
    if(minans!=1<<30) cout<<minans<<endl;
    else cout<<-1<<endl;
    return 0;
}
void dfs(int x,int y,int mou){
	if(mou==0||times>m*n||times>minans) return;
	if(a[x][y]==4) mou=6;
    if(x==lx&&y==ly) minans=min(times,minans);
    else{
        for(int i=0;i<4;i++){
            tx=x+dir[i][0];
            ty=y+dir[i][1];
            if(tx<=0||tx>n||ty<=0||ty>m||a[tx][ty]==0) continue;
            //边界判断和是否撞墙
            ++times;
            dfs(tx,ty,mou-1);
			--times;
        }
    }
}
