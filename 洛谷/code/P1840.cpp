// https://www.luogu.com.cn/problem/P1840
// 题意：数轴上 1 到 n 的点起初都是黑色。每次把闭区间 [l_i,r_i] 内的点染白，输出操作后剩余的黑点数。
// 数据范围：1 ≤ n,m ≤ 2×10^5，1 ≤ l_i ≤ r_i ≤ n。
// 算法标签：并查集

#include <cstdio>
using namespace std;

int st[200005];

int getfa(int x){
	return x==st[x]?x:st[x]=getfa(st[x]);
}

void unio(int a,int b){
	st[getfa(b)] = getfa(a);
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);

	int blkn = n;
	for(int i=1; i<=n+1; ++i)
	{
		st[i] = i;
	}
	for(int i=1; i<=m; ++i)
	{
		int li,ri;
		scanf("%d%d",&li,&ri);

		int t = getfa(li);
		while(t<=ri)
		{
			unio(t+1,t);
			t = getfa(t);
			--blkn;
		}

		printf("%d\n",blkn);
	}
}
