#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll delta[80005],anss[80005];
ll n,opt,mod,minn,maxx,ans,now,final;

void ask(ll l,ll r){
	now=ans=0;
	for(ll i=1;i<=r;i++)
	{
		now+=delta[i];
		if(i>=l&&(now*i)%mod>=minn&&(now*i)%mod<=maxx)
            ans++;
	}
	printf("%lld\n",ans);
}

int main()
{
	cin>>n>>opt>>mod>>minn>>maxx;
	for(int i=1;i<=opt;i++){
		char c;
		cin>>c;
		if(c=='A'){
			ll l,r,x;
			scanf("%lld%lld%lld",&l,&r,&x);
			delta[l]+=x;
			delta[r+1]-=x;
		}else if(c=='Q'){
			ll l,r;
			ans=0;
			scanf("%lld%lld",&l,&r);
			ask(l,r);
		}
	}
	scanf("%lld",&final);
	now=0;
	for(ll i=1;i<=n;i++){
		now+=delta[i];
		anss[i]=((now*i)%mod<=maxx&&(now*i)%mod>=minn)?1:0;
		anss[i]+=anss[i-1];
	}
	while(final--){
		ll l,r;
		scanf("%lld%lld",&l,&r);
		printf("%lld\n",anss[r]-anss[l-1]);
	}
	return 0;
}
