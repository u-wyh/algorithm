#include<bits/stdc++.h>
#define int long long
const int mod = 1e9 + 7;
using namespace std;
int a[105][105], dp[105][105];

int read(){
	int i = 0, f = 1;
	char ch;
	for (ch = getchar(); (ch < '0' || ch > '9') && ch != '-'; ch = getchar());
	if (ch == '-')
	{
		f = -1;
		ch = getchar();
	}
	for (; ch >= '0' && ch <= '9'; ch = getchar())
		i = (i << 3) + (i << 1) + (ch ^ 48);
	return i * f;
}
signed main()
{
	int r = read(), c = read(), k = read();
	for (int i = 1; i <= r; i++)
		for (int j = 1; j <= c; j++)
			a[i][j] = read();
	dp[1][1] = 1;
	for (int i = 2; i <= r; i++)
		for (int j = 2; j <= c; j++)
			for (int t1 = 1; t1 < i; t1++)
				for (int t2 = 1; t2 < j; t2++)
					if (a[t1][t2] != a[i][j]) dp[i][j] = (dp[i][j] + dp[t1][t2]) % mod;
	printf("%lld", dp[r][c]);
	return 0;
}
