#include<cstdio>
#include<cstring>
#include<iostream>
#define MAXN 205
using namespace std;
int n, m, sx, sy, K, ans, dp[MAXN][MAXN];
int dx[5] = {0, -1, 1, 0, 0}, dy[5] = {0, 0, 0, -1, 1};
struct node{int dp, pos;}q[MAXN]; //q为单调递减队列，要存位置信息用来计算共走了几步
char map[MAXN][MAXN];
void work(int x, int y, int len, int d) //第k个区间的时长为len，方向为d，起点坐标x,y
{
	int head = 1, tail = 0;
	for(int i = 1; x >= 1 && x <= n && y >= 1 && y <= m; i++, x += dx[d], y += dy[d])
		if(map[x][y] == 'x') head = 1, tail = 0; //遇到障碍，清空队列
		else
		{
			while(head <= tail && q[tail].dp + i - q[tail].pos < dp[x][y]) tail--;
			q[++tail] = node{dp[x][y], i}; //当前值入队列
			if(q[tail].pos - q[head].pos > len) head++; //队列长度超过len时队首弹出
			dp[x][y] = q[head].dp + i - q[head].pos; //最优解是队首元素+移动距离
			ans = max(ans, dp[x][y]); //记录结果
		}
}
int main()
{
	scanf("%d%d%d%d%d", &n, &m, &sx, &sy, &K);
	for(int i = 1; i <= n; i++) scanf("%s", map[i] + 1);
	memset(dp, 0xf3, sizeof(dp));
	dp[sx][sy] = 0; //初始化，只有初始位置是0，其他都是负无穷
	for(int k = 1, s, t, d, len; k <= K; k++)
	{
		scanf("%d%d%d", &s, &t, &d);
		len = t - s + 1;
		if(d == 1) for(int i = 1; i <= m; i++) work(n, i, len, d);
		if(d == 2) for(int i = 1; i <= m; i++) work(1, i, len, d);
		if(d == 3) for(int i = 1; i <= n; i++) work(i, m, len, d);
		if(d == 4) for(int i = 1; i <= n; i++) work(i, 1, len, d);
	}
	printf("%d", ans);
	return 0;
}
