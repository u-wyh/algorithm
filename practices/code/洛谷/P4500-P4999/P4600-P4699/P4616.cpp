// https://www.luogu.com.cn/problem/P4616
// 题意：1 到 n 号城市初始不连通，
// 第 i 天在所有
// 满足 gcd(a, b) = m - i + 1 的城市 a, b 间修一条路，
// 共修 m 天
// q 次询问两个城市最早第几天连通。
// 数据范围：1 <= n, q <= 10^5，1 <= m <= n。
// 难度评分：2000（洛谷分级换算）
// 算法标签：Kruskal重构树、树链剖分、并查集
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#define reg register
using namespace std;
const int N=2e5+5;
struct node
{
	int to,nxt;
}edge[N*20];
int n,m,num,head[N],cnt,f[N],tot[N],dep[N];
int tim,idx[N],top[N],fa[N],son[N],w[N];
inline int read()
{
	int x=0,w=1;
	char c=getchar();
	while (!isdigit(c)&&c!='-') c=getchar();
	if (c=='-') c=getchar(),w=-1;
	while (isdigit(c))
	{
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*w;
}
inline void add_edge(int from,int to)
{
	edge[++num]=(node){to,head[from]}; head[from]=num;
	edge[++num]=(node){from,head[to]}; head[to]=num;
}
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
void dfs(int k,int father,int deep)
{
	int bigson=0;
	fa[k]=father; dep[k]=deep; tot[k]=1;
	for (reg int i=head[k];i;i=edge[i].nxt)
	{
		int v=edge[i].to;
		if (v==father) continue;
		dfs(v,k,deep+1); tot[k]+=tot[v];
		if (bigson<tot[v]) bigson=tot[v],son[k]=v;
	}
}
void dfs(int k,int tp)
{
	idx[k]=++tim; top[k]=tp;
	if (!son[k]) return; dfs(son[k],tp);
	for (reg int i=head[k];i;i=edge[i].nxt)
	{
		int v=edge[i].to;
		if (!idx[v]) dfs(v,v);
	}
}
inline int getlca(int x,int y)
{
	while (top[x]!=top[y])
	{
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
int main()
{
	n=cnt=read(),m=read();
	for (reg int i=1;i<=(n<<1);i++) f[i]=i;
	for (reg int i=m;i;i--)
	{
		for (reg int j=(i<<1);j<=n;j+=i)
		{
			int u=find(i),v=find(j);
			if (u==v) continue;
			w[f[u]=f[v]=++cnt]=m-i+1;
			add_edge(u,cnt); add_edge(v,cnt);
		}
	}
	dfs(cnt,0,1); dfs(cnt,cnt);
	for (reg int T=read();T;T--) printf("%d\n",w[getlca(read(),read())]);
	return 0;
}
