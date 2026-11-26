// https://www.luogu.com.cn/problem/P5566
// 题意：给定结点数 N（不计前端空结点），求所有含 N 个内结点的合法红黑树中，红色内结点个数的最小值和最大值。
// 输入正整数 N；分两行输出最小和最大红色内结点个数。
// 数据范围：N <= 5000。
#include <bits/stdc++.h>
int n, ans, k;
int main()
{
	scanf("%d", &n);
	k = n + 1;
	while (k > 1)
	{
		ans += k & 1;
		k >>= 1;
	}
	printf("%d\n", ans);
	k = n + 1;
	ans = 0;
	while (k > 1)
	{
		if (k == 2)
			ans++, k--;
		else if ((k & 3) == 1)
			ans += ((k >> 2) << 1) - 1, k >>= 2, k++;
		else if ((k & 3) == 2)
			ans += ((k >> 2) << 1), k >>= 2, k++;
		else if ((k & 3) == 3)
			ans += ((k >> 2) << 1) + 1, k >>= 2, k++;
		else
			ans += (k >> 1), k >>= 2;
	}
	printf("%d", ans);
	return 0;
}