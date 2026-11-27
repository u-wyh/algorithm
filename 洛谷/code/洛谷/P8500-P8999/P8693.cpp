// https://www.luogu.com.cn/problem/P8693
// 题意：输入 n, k 和 n*n 字符网格（+ 空地，* 障碍）；
// 初始时刻 0 中心在 (3, 3) 占 5*5 区域，
// 每单位时间可上下左右移动 1 格或原地不动，时刻 k 变为占 3*3
// 时刻 2*k 变为占 1*1（占用区域内不能包含 * 或越界），
// 输出中心到达 (n-2, n-2) 的最少时间。
// 数据范围：1 <= n <= 300，1 <= k <= 1000。
// 算法标签：广度优先搜索
#include <bits/stdc++.h>
#define ll long long
#define setp setprecision
#define mem(a, m) memset(a, m, sizeof(a));
using namespace std;

int n, k;
int ans = 0x3f3f3f;
int a[305][305];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
bool vis[305][305];
struct node {
	int x, y;//坐标
	int Time;//时间
	int size;//小明大小
};
bool check(int x, int y, int size)
{
	if(vis[x][y])	return false;
	for(int i=x-size;i<=x+size;i++)
		for(int j=y-size;j<=y+size;j++)
			if(i < 1 || i > n || j < 1 || j > n || a[i][j])
				return false;
	return true;
}
int work(int Time)
{
	if(Time < k)	return 2;
	else if(Time < 2 * k)	return 1;
	else	return 0;
}
void bfs()
{
	queue <node> q;
	vis[3][3] = 1;
	q.push((node){3, 3, 0, 2});
	while(!q.empty())
	{
		node t = q.front();
		q.pop();
		if(t.x == n - 2 && t.y == n - 2)//到达终点，停止搜索
		{
			cout << t.Time;
			return ;
		}
		if(t.size != 0)	q.push((node){t.x, t.y, t.Time+1, work(t.Time+1)});//站着不动
		for(int i=0;i<4;i++)
		{
			int X = t.x + dx[i];
			int Y = t.y + dy[i];
			if(check(X, Y, t.size))//判断
			{
				vis[X][Y] = 1;
				q.push((node){X, Y, t.Time+1, work(t.Time+1)});
			}
		}
	}
}
int main()
{
	cin >> n >> k;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			char c;
			cin >> c;
			if(c == '*')	a[i][j] = 1;
			else	a[i][j] = 0;
		}
	}
	bfs();
	return 0;
}
