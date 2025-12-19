#include<bits/stdc++.h>
#define ll long long
#define Maxn 2000005
#define next Next
using namespace std;
ll read()
{
	ll r=0,f=1;char c=getchar();
	while((c<'0'||c>'9')&&(c!='-')) c=getchar();
	if(c=='-') f=-1,c=getchar();
	while(c>='0'&&c<='9') r=r*10+c-'0',c=getchar();
	return r*f;
}
priority_queue< pair<ll,ll> >q,q1;
ll ans,n,m,tot,tot1,ver[Maxn],head[Maxn],next[Maxn],edge[Maxn],d[Maxn],v[Maxn];
ll ver1[Maxn],head1[Maxn],next1[Maxn],edge1[Maxn],d1[Maxn],v1[Maxn];
void add(ll x,ll y,ll z)
{
	ver[++tot]=y;
	next[tot]=head[x];
	head[x]=tot;
	edge[tot]=z;
}
void add1(ll x,ll y,ll z)
{
	ver1[++tot1]=y;
	next1[tot1]=head1[x];
	head1[x]=tot1;
	edge1[tot1]=z;
}
void dijkstra(ll s)
{
	memset(d,0x7f,sizeof(d));
	memset(v,0,sizeof(v));
	d[s]=0;
	q.push(make_pair(0,s));
	while(q.size())
	{
		ll x=q.top().second;q.pop();
		if(v[x]) continue;
		v[x]=1;
		for(int i=head[x];i;i=next[i])
		{
			ll y=ver[i],z=edge[i];
			if(d[y]>d[x]+z)
			{
				d[y]=d[x]+z;
				q.push(make_pair(-d[y],y));
			}
		}
	}
}
void dijkstra1(ll s)
{
	memset(d1,0x7f,sizeof(d1));
	memset(v1,0,sizeof(v1));
	d1[s]=0;
	q1.push(make_pair(0,s));
	while(q1.size())
	{
		ll x=q1.top().second;q1.pop();
		if(v1[x]) continue;
		v1[x]=1;
		for(int i=head1[x];i;i=next1[i])
		{
			ll y=ver1[i],z=edge1[i];
			if(d1[y]>d1[x]+z)
			{
				d1[y]=d1[x]+z;
				q1.push(make_pair(-d1[y],y));
			}
		}
	}
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=m;i++)
	{
		ll x=read(),y=read(),z=read();
		add(x,y,z);
		add1(y,x,z);
	}
	dijkstra(1);
	dijkstra1(1);
	for(int i=2;i<=n;i++)
	{
		ans+=d[i]+d1[i];
	}
	cout<<ans<<endl;
	return 0;
}
