#include<bits/stdc++.h>
using namespace std;

struct node{
	int next,to;
	long long dis;
}e[10001];
int n,m,ne,p,q;
int h[10001];
long long dis[1001],t;
bool vis[1001];
string a,b;
map<string,int> ma;

void add(int u,int v,long long w)
{
	e[++ne].next=h[u];
	e[ne].dis=w,e[ne].to=v,h[u]=ne;
}

void dij(int s)
{
	for(int i=1;i<=n;i++) dis[i]=1e14;
	memset(vis,0,sizeof(vis));
	priority_queue<pair<long long,int> > qu;
	qu.push(make_pair(0,s));
	dis[s]=0;
	while(!qu.empty())
	{
		int u,v;
		u=qu.top().second;qu.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=h[u];i;i=e[i].next)
		{
			v=e[i].to;
			if(dis[v]>dis[u]+e[i].dis)
			{
				dis[v]=dis[u]+e[i].dis;
				qu.push(make_pair(-dis[v],v));
			}
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		cin>>a>>b>>t;
		if(!ma.count(a)) ma[a]=++p;
		if(!ma.count(b)) ma[b]=++p;
		add(ma[a],ma[b],t);
	}
	scanf("%d",&q);
	while(q--)
	{
		cin>>a>>b;
		int g1,g2;
		g1=ma[a],g2=ma[b];
		dij(g1);
		if(dis[g2]==1e14) printf("Roger\n");
		else printf("%lld\n",dis[g2]);
	}
	return 0;
}
