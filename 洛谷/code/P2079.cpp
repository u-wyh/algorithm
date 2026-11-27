// https://www.luogu.com.cn/problem/P2079
// 题意：从 N 道菜中选菜，总价不超过 V，且小明的喜爱值之和至少为 0。求小红的喜爱值之和最大是多少，若最大值为负则输出 -1。
// 数据范围：1 ≤ N ≤ 100，1 ≤ V ≤ 500，价格 C_i 为正整数，小明和小红的单项喜爱值绝对值分别不超过 5 和 1000。
// 算法标签：动态规划、0-1背包

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int x[105],y[105],c[105];
int dp[505][1005];

int main()
{
	int n,v;
	cin >> n >> v;
	for (int i = 1;i <= n;i++)
	{
		cin >> c[i] >> x[i] >> y[i];
	}
	memset(dp,-0x3f,sizeof(dp));//初始化
	dp[0][500] = 0;//平移
	for (int i = 1;i <= n;i++)
	{
		for (int j = v;j >= c[i];j--)
		{
			if (x[i] >= 0)//判断枚举顺序
			{
				for (int k = 1000;k >= x[i];k--)
				{
					dp[j][k] = max(dp[j][k],dp[j - c[i]][k - x[i]] + y[i]);
				}
			}
			else
			{
				for (int k = 0;k <= 1000 + x[i];k++)
				{
					dp[j][k] = max(dp[j][k],dp[j - c[i]][k - x[i]] + y[i]);
				}
			}
		}
	}
	int ans = -1;
	for (int i = 0;i <= v;i++)
	{
		for (int j = 500;j <= 1000;j++)
		{
			ans = max(ans,dp[i][j]);
		}
	}
	cout << ans << endl;
	return 0;
}
