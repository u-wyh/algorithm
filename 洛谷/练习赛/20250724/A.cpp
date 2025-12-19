#include <bits/stdc++.h>
#define lln long long
using namespace std;
const int MAX = 4e6 + 5;
const int MOD = 998244353;
int n, m, k, a[MAX], mx;
int dir[2][3][2] = { {{-1,0},{0,1},{1,0}},{{-1,0},{0,-1},{1,0}} };
struct node { int x, y; }cur;
struct line { int tp, dn; };
queue<node>que;
vector<line>vec;
void bfs()
{
	int p, q;
	que.push({ 0,m - 1 });
	a[m - 1] = 2;
	while (que.size())
	{
		cur = que.front();
		que.pop();
		for (int d = 0;d < 3;d++)
		{
			p = cur.x + dir[1][d][0];
			q = cur.y + dir[1][d][1];
			if (p < n && p >= 0 && q < m && q >= 0 && !a[p * m + q])
			{
				a[p * m + q] = 2;
				que.push({ p,q });
			}
		}
	}
	que.push({ 0,0 });
	if (!a[0])a[0] = 4;
	else a[0] = 3;
	while (que.size())
	{
		cur = que.front();
		que.pop();
		for (int d = 0;d < 3;d++)
		{
			p = cur.x + dir[0][d][0];
			q = cur.y + dir[0][d][1];
			if (p < n && p >= 0 && q < m && q >= 0 && (!a[p * m + q] || a[p * m + q] == 2))
			{
				if(!a[p * m + q]) a[p * m + q] = 4;
				else a[p * m + q] = 3;
				que.push({ p,q });
			}
		}
	}
	mx = 0;
	for (int j = 1;j < m;j++)
	{
		int c = 0;
		for (int i = 0;i < n;i++)
		{
			if (a[i * m + j]==4)c++;
			else if (c)vec.push_back({ i - c,i - 1 }), c = 0;
		}
		if(c)vec.push_back({ n - c,n - 1 }), c = 0;
		for (auto it : vec)
		{
			c = 1;
			for (int i = it.tp;i <= it.dn;i++)
			{
				if (a[i * m + j - 1] > 4)
				{
					c = max(a[i * m + j - 1] - 4 + 1, c);
				}
			}
			mx = max(mx, c);
			for (int i = it.tp;i <= it.dn;i++)a[i * m + j] = 4 + c;
		}
		vec.clear();
	}
}
void solve()
{
	cin >> n >> m >> k;
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < m;j++)
		{
			char t; cin >> t;
			a[i * m + j] = t - '0';
		}
	}
	bfs();
	cout << (mx >= k ? "Yes" : "No") << "\n";
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T = 1;
	cin >> T;
	while (T--)solve();
}