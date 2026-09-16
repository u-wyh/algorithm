#include<bits/stdc++.h>
using namespace std;
const int maxn=1000005;
int n,k,t,len=0x3f3f3f3f;
int id[maxn],b;
struct node{
	int pos;
	int val;
}f[maxn];
bool cmp(node a,node b)
{
	return a.pos<b.pos;
}
int main()
{
	memset(id,-1,sizeof(id));
	scanf("%d%d",&n,&k);
	for(int i=1;i<=k;i++)
	{
		scanf("%d",&t);
		for(int j=1;j<=t;j++)
		{
			scanf("%d",&f[++b].pos);
			f[b].val=i;
		}
	}
	sort(f+1,f+n+1,cmp);
	int hd=1,cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(id[f[i].val]==-1) cnt++;
		id[f[i].val]=f[i].pos;
		while(hd<=i&&f[hd].pos!=id[f[hd].val]) hd++;
		if(cnt==k&&f[i].pos-f[hd].pos<len) len=f[i].pos-f[hd].pos;
	}
	printf("%d",len);
	return 0;
}
