// https://www.luogu.com.cn/problem/P5836
// 题意：一棵 N 个农场的树上每点养 G 或 H 种奶牛，M 个朋友各有偏好的品种和树上行走路径 (A_i, B_i)，判断每人沿途能否喝到偏好的牛奶。
// 输入 N, M、品种串、树边及 M 个询问；输出长为 M 的 01 串（1 表示满意）。
// 数据范围：1 <= N, M <= 10^5。
// 算法标签：并查集
#include<bits/stdc++.h>
using namespace std;
int fa[100010],ans[100010],M,N;
char col[100010];
int find(int x)
{
	if(x==fa[x])	return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y)
{
	fa[find(x)]=find(y);
}
int main()
{
	int cnt=0;
	cin>>N>>M;
	for(int i=1;i<=N;i++)
	{
		fa[i]=i;
		cin>>col[i];
	}
	for(int i=1;i<=N-1;i++)
	{
		int u,v;cin>>u>>v;
		if(col[u]==col[v])	merge(u,v);
	}
	for(int i=1;i<=M;i++)
	{
		int a,b;	cin>>a>>b;
		char c;		cin>>c;
		if(find(a)==find(b)&&col[a]!=c)		ans[++cnt]=0;//判断路径上是否有偏好的牛奶
		else	ans[++cnt]=1;
	}
	for(int i=1;i<=cnt;i++)	cout<<ans[i];
	return 0;
}
