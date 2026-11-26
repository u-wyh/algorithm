// https://www.luogu.com.cn/problem/P8657
// 题意：输入 n, m 和 m 条无向边 (u, v)（无重边自环、图连通且从任意边到达任意点后都有其他边可走）；
// 从每个城市 i 出发随机等概率沿非来路边行走（每条边耗时 1），直到首次回到 i 为止
// 输出 n 行实数表示从每个城市出发的期望时间（绝对或相对误差 <= 10^-9）。
// 数据范围：4 <= n <= 21，1 <= u, v <= n。
#include<bits/stdc++.h>
using namespace std;

int n, m, a, b, sum, d[100];

int main()
{
	cin>>n>>m;
	while(m--) cin>>a>>b, d[a] ++, d[b] ++;
	for(int i = 1;i <= n;i ++) sum += d[i];
	for(int i = 1;i <= n;i ++) printf("%.12lf\n", 1.0*sum/d[i]);
	return 0;
}

