#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n,m,md;
ll a[400005],sum[400005],mu[400005],add[400005],lll[400005],rrr[400005];
#define ls(x) x<<1
#define rs(x) x<<1|1
void build(ll p,ll l,ll r){
	lll[p]=l,rrr[p]=r,mu[p]=1;
	if(l==r){
		sum[p]=a[l]%md;
		return;
	}
	ll mid=(l+r)>>1;
	build(ls(p),l,mid);
	build(rs(p),mid+1,r);
	sum[p]=sum[ls(p)]+sum[rs(p)]%md;
}
void pushdown(ll p){
	sum[ls(p)]=(mu[p]*sum[ls(p)]+(rrr[ls(p)]-lll[ls(p)]+1)*add[p]%md)%md;
	sum[rs(p)]=(mu[p]*sum[rs(p)]+(rrr[rs(p)]-lll[rs(p)]+1)*add[p]%md)%md;
	mu[ls(p)]=(mu[p]*mu[ls(p)])%md;
	mu[rs(p)]=(mu[p]*mu[rs(p)])%md;
	add[ls(p)]=(mu[p]*add[ls(p)]+add[p])%md;
	add[rs(p)]=(mu[p]*add[rs(p)]+add[p])%md;
	mu[p]=1,add[p]=0;
}
void addd(ll p,ll l,ll r,ll k){
	if(lll[p]>=l && rrr[p]<=r){
		add[p]+=k;
		add[p]%=md;
		sum[p]+=(rrr[p]-lll[p]+1)*k;
		sum[p]%=md;
		return;
	}
	pushdown(p);
	sum[p]=(sum[ls(p)]+sum[rs(p)])%md;
	ll mid=(lll[p]+rrr[p])>>1;
	if(l<=mid)addd(ls(p),l,r,k);
	if(mid<r)addd(rs(p),l,r,k);
	sum[p]=(sum[ls(p)]+sum[rs(p)])%md;
}
void mul(ll p,ll l,ll r,ll k){
	if(lll[p]>=l && rrr[p]<=r){
		add[p]*=k,add[p]%=md;
		mu[p]*=k,mu[p]%=md;
		sum[p]*=k,sum[p]%=md;
		return;
	}
	pushdown(p);
	sum[p]=(sum[ls(p)]+sum[rs(p)])%md;
	ll mid=(lll[p]+rrr[p])>>1;
	if(l<=mid)mul(ls(p),l,r,k);
	if(mid<r)mul(rs(p),l,r,k);
	sum[p]=(sum[ls(p)]+sum[rs(p)])%md;
}
ll query(ll p,ll l,ll r){
	if(lll[p]>=l && rrr[p]<=r)return sum[p];
	pushdown(p);
	ll v=0,mid=(lll[p]+rrr[p])>>1;
	if(l<=mid)v+=query(ls(p),l,r),v%=md;
	if(mid<r)v+=query(rs(p),l,r),v%=md;
	return v;
}
int main() {
	cin>>n>>md;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	build(1,1,n);
	cin>>m;
	while(m--){
		ll x,y,typ;
		scanf("%lld%lld%lld",&typ,&x,&y);
		if(typ==1){
			ll z;
			scanf("%lld",&z);
			mul(1,x,y,z);
		}else if(typ==2){
			ll z;
			scanf("%lld",&z);
			addd(1,x,y,z);
		}else printf("%lld\n",query(1,x,y));
	}
	return 0;
}
