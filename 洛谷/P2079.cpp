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
	memset(dp,-0x3f,sizeof(dp));//≥ı ºªØ
	dp[0][500] = 0;//∆Ω“∆
	for (int i = 1;i <= n;i++)
	{
		for (int j = v;j >= c[i];j--)
		{
			if (x[i] >= 0)//≈–∂œ√∂æŸÀ≥–Ú
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
