#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>
#define ll long long
#define db double
using namespace std;
inline int read()
{
	char ch=getchar();
	int a=0,x=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') x=-x;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		a=(a<<1)+(a<<3)+(ch^48);
		ch=getchar();
	}
	return a*x;
}
const int N=1005;
int n,Edge;
int cost[N],vis[N],f[N][N];
ll cnt[N];
void Dijkstra()
{
	for(int i=1;i<n;i++)                    //进行n-1轮松弛操作
	{
		int Min=1e9,u;
		//每次一定可以找到一个目前最低价格的  他一定无法被优化了
		for(int j=1;j<=n;j++)               //取一个得出最小花费的药水来更新别的药水
		{
			if(!vis[j]&&cost[j]<Min)        //只取没进行过松弛操作的j,以免造成时间浪费
			{
				u=j;Min=cost[j];
			}
		}
		vis[u]=1;                           //记录一下u点已经松弛过它的出边终点了
		for(int v=1;v<=n;v++)
		{
			if(vis[v]&&f[u][v])             //找另外已经得出最小花费的药水(松弛过了其他点的药水)
			{
				int w=f[u][v];              //它们所能合成的药水
				if(cost[w]==cost[u]+cost[v])//如果通过u和v合成的花费和原来一样
				{
					cnt[w]+=cnt[u]*cnt[v];  //方法又多了cnt[u]*cnt[v]种
				}
				else if(cost[w]>cost[u]+cost[v]) //如果花费更少
				{
					cost[w]=cost[u]+cost[v];//松弛成功
					cnt[w]=cnt[u]*cnt[v];   //更新记录方案数
				}
			}
		}
	}
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++) cost[i]=read();   //每个药水从商店购买的初始花费
	for(int i=1;i<=n;i++) cnt[i]=1ll;       //记录最小花费方案数,初始化为1,表示从商店购买
	int u,v,w;
	while(cin>>u>>v>>w)
	{
		u++;v++;w++;                        //编号+1
		f[u][v]=f[v][u]=w;                  //表示 u+v->w
	}
	Dijkstra();
	printf("%d %lld\n",cost[1],cnt[1]);     //输出最小花费和方案数
	return 0;
}
