#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int MAXN = 1500 + 1;
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

int n, m;
int st_x, st_y;
int vis[MAXN][MAXN][3];//vis[x][y]表示的是对于所有位置（只要在原图上对应的是xy的）的点
//vis[x][y][0]表示的是这个位置是否有任何一个只要在原图上对应的是xy的节点来过
//vis[x][y][1]表示的是如果来过 上一次来的真实位置x位置
bool fl, a[MAXN][MAXN];
char ch;

void dfs(int x, int y, int lx, int ly) {
    //xy分别是对应在原始中心图的位置
    //lx ly分别对应的是实际应该的位置，即坐标可能越界，这个界指的是原始中心图的界
    //为什么这么做  是为了防止重新走回来所导致的结束
    //为什么一定要加上lx ly，因为xy对应的vis会被多次访问 不能以此来判断是否可以结束和向下搜索
	if(fl) return;
	if(vis[x][y][0] && (vis[x][y][1]!=lx || vis[x][y][2]!=ly)) {
		fl = 1;
		return;
	}
	//如果可以运行到这里 那么一定有这个位置没有任何节点来过
	vis[x][y][1] = lx, vis[x][y][2] = ly, vis[x][y][0] = 1;
	for(int i=0; i<4; ++i) {
		int xx = (x + dx[i] + n) % n, yy = (y + dy[i] + m) % m;//对应原图的位置
		int lxx = lx + dx[i], lyy = ly + dy[i];//真实的位置
		if(!a[xx][yy]) {
            //表示可以走
			if(vis[xx][yy][1]!=lxx || vis[xx][yy][2]!=lyy || !vis[xx][yy][0])
				dfs(xx, yy, lxx, lyy);//不走回头路  要么以前对应原图根本没走过  要么走过但不是这个节点
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	while(cin >> n >> m) {
		fl = 0;
		memset(a, 0, sizeof(a));
		memset(vis, 0, sizeof(vis));
		for(int i=0; i<n; ++i)
			for(int j=0; j<m; ++j) {
				cin >> ch;
				if(ch == '#') a[i][j] = 1;
				if(ch == 'S') st_x = i, st_y = j;
			}
		dfs(st_x, st_y, st_x, st_y);
		if(fl) puts("Yes");
		else puts("No");
	}
	return 0;
}
