#include<bits/stdc++.h>
using namespace std;
struct node{long long a,b;}spe[500005];
inline bool cmp(node a,node b){return (a.b!=b.b)?a.b<b.b:a.a<b.a;}
long long n,a1,b1,cnt,maxn,ans,sum,lasa;
int main()
{
	scanf("%lld",&n);
	for(long long i=1;i<=n;++i)
	{
		scanf("%lld%lld",&a1,&b1);
		if(a1>b1) spe[++cnt].a=a1,spe[cnt].b=b1;
		maxn=max(maxn,max(a1,b1));
	}
	ans=0x3f3f3f3f3f3f3f3f;
	sort(spe+1,spe+cnt+1,cmp);
	for(long long i=1;i<=cnt;++i)
	{
		ans=min(ans,sum+maxn-spe[i].b);
		sum+=2*(max(0ll,spe[i].a-max(lasa,spe[i].b))),lasa=max(lasa,spe[i].a);
	}
	printf("%lld",min(sum,ans)+maxn);
	return 0;
}
