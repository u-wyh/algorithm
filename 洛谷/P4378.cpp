# include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int a[N],tmp[N],c[N];
int n,T;
void update(int x){for (;x<=n;x+=x&-x)c[x]++;}
int query(int x){int ret=0;for (;x;x-=x&-x) ret+=c[x];return ret;}
int main()
{
	scanf("%d",&n); tmp[0]=n;
	for (int i=1;i<=n;i++) scanf("%d",&a[i]),tmp[i]=a[i];
	sort(tmp+1,tmp+tmp[0]+1);
	T=unique(tmp+1,tmp+1+tmp[0])-tmp-1;
	int ans=0;
	for (int i=1;i<=n;i++) {
		int w=lower_bound(tmp+1,tmp+1+T,a[i])-tmp;
		update(w);
		ans=max(i-query(w),ans);
	}
	printf("%d\n",ans+1);
	return 0;
}
