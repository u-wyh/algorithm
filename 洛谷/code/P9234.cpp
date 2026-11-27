// https://www.luogu.com.cn/problem/P9234
// 题意：有 n 个瓜，第 i 个重量为 A_i，每个瓜最多劈一刀变成等重的两份（每份重 A_i / 2）。
// 求选出总重量恰好为 m 的瓜（或半瓜）所需的最少劈瓜数；
// 若无法凑出总重 m 则输出 -1。
// 题意：第一行输入 n, m，第二行输入 A_1..A_n；输出一行一个整数。
// 数据范围：1 <= n <= 30，1 <= A_i <= 10^9，1 <= m <= 10^9。
// 算法标签：折半搜索、深度优先搜索、哈希表
#include <iostream>
#include <algorithm>
#include <unordered_map>

#define i64 long long
#define reg register
#define qwq puts("fzy qwq ~");

using namespace std;

const int inf = 0x7fffffff;

int n, mid, ans = inf; int m;
int a[31]; bool spt[31];
unordered_map<int, int> tb;

inline void dfs1(int p, int w, int k)
{
	if (w > m || k > ans || (tb.count(w) && tb[w] < k)) return; // 剪枝
	if (w == m) { ans = min(ans, k); return; } // 不用搜了
	if (p == mid + 1)
	{
		if (w <= m)
		{
			if (tb.count(w))
				tb[w] = min(tb[w], k);
			else 
				tb[w] = k;
			// 记录目前能得到质量量 w 最少需要的刀数
		}
		return;
	}
	dfs1(p + 1, w, k);				 // 生瓜蛋子，不要了
	dfs1(p + 1, w + a[p], k + 1);	 // 劈一刀看看
	dfs1(p + 1, w + (a[p] << 1), k); // 一眼保熟，不用劈了
}
inline void dfs2(int p, int w, int k) // 大部同上
{
	if (w > m || k > ans) return;
	if (w == m) { ans = min(ans, k); return; }
	if (p == n + 1)
	{
		if (w <= m && tb.count(m - w))
			ans = min(ans, tb[m - w] + k); // 若能够得到刚好质量 m 的瓜，更新答案
		return;
 	}
	dfs2(p + 1, w, k);
	dfs2(p + 1, w + a[p], k + 1);
	dfs2(p + 1, w + (a[p] << 1), k);
}


int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> m;
	m <<= 1; mid = n >> 1;
	// 预先把瓜的质量翻倍，防止出现小数
	for (reg int i = 1; i <= n; ++i)
		cin >> a[i];
		
	sort(a + 1, a + n + 1);
	dfs1(1, 0, 0);
	dfs2(mid + 1, 0, 0);
	
	cout << (ans == inf ? -1 : ans) << endl;
	return 0;
}
