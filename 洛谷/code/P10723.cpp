// https://www.luogu.com.cn/problem/P10723
// 题意：给一棵树和每个点的黑白颜色。一次可把一个白点染黑，要求最后删去所有白点后，黑点仍构成一棵树。输出最少要染黑几个点。
// 数据范围：1 ≤ n ≤ 10^5，颜色值为 0 或 1。

#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
const int mod=1e9+7;
const int maxn=1e6+10;
int n,d[maxn];
vector<int> G[maxn];
bool siz[maxn];
void dfs(int x,int fa)
{
	if(d[x])siz[x]=1;
	for(auto y : G[x])
	{
		if(y==fa)continue;
		dfs(y,x);
		siz[x]|=siz[y];
	}
}
int du[maxn];
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)d[i]=read();
	bool ff=0;
	for(int i=1;i<=n;i++)ff|=d[i];
	if(!ff)return 0*printf("%lld\n",0);
	for(int i=1;i<n;i++)
	{
		int x=read(),y=read();
		G[x].push_back(y);
		G[y].push_back(x);
		du[x]++;du[y]++;
	}
	int root=1;
	for(int i=1;i<=n;i++)if(d[i]==1)root=i;
	dfs(root,0);
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		if(d[i]==0&&siz[i])ans++;
	}
	cout<<ans;
	return 0;
}
