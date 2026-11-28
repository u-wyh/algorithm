// https://www.luogu.com.cn/problem/P9484
// 题意：多组数据（共 T 组）。
// 每组图有 n 个节点 1..n，
// 当且仅当 gcd(i, j) = i
// 且 lcm(i, j) = j（即 i | j）时
// i 和 j 之间有一条边权为 |i - j| 的无向边。
// q 次询问 x 到 y 的最短路径长度。
// 题意：第一行输入 T，每组输入 n, q 及 q 行 x, y；
// 输出每组对应的 q 行正整数。
// 数据范围：1 <= T <= 10^6，1 <= n, q <= 10^6，
// 1 <= x, y <= n
// 1 <= sum(n), sum(q) <= 10^6。
// 难度评分：1000（洛谷分级换算）
// 算法标签：欧几里得算法
#include<bits/stdc++.h>
int t,n,q;
int x,y;
int gcd(int a,int b)
{
	while(b^=a^=b^=a%=b);
	return a;
}
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>q;
		for(int i=1;i<=q;i++)
		{
			cin>>x>>y;
			cout<<x+y-2*gcd(x,y)<<'\n';
		}
	 }
	return 0;
}
