#include <queue>
#include <cstdio>
#include <vector>

using namespace std;

vector<int> web[100005]; //邻接表
int a[100005]; //A
int ind[100005]; //入度
int f[100005][15];
/*
f[i][j] 代表从xxx节点到i节点，末尾为j的最长不下降子序列长度
*/

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d", a + i);
	}
	for(int i=1;i<=m;i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		web[u].push_back(v); //建图
		ind[v]++; //入度++
	}
	queue<int> q; //拓扑排序
	for(int i=1;i<=n;i++)
	{
		if(ind[i] == 0) //入度为0，进队
		{
			q.push(i);
		}
		f[i][a[i]] = 1; //f初始
	}
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int v : web[u])
		{
			if(!--ind[v]) q.push(v); //入度变为0
			for(int i=1;i<=a[v];i++)
			{
				if(f[u][i] + 1 > f[v][a[v]]) f[v][a[v]] = f[u][i] + 1; //第一种转移
			}
			for(int i=1;i<=10;i++)
			{
				if(f[u][i] > f[v][i]) f[v][i] = f[u][i]; //第二种转移
			}
		}
	}
	int maxn = 0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=10;j++)
		{
			if(f[i][j] > maxn) maxn = f[i][j]; //取最大
		}
	}
	printf("%d\n", maxn);
	return 0;
}
