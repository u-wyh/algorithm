// https://www.luogu.com.cn/problem/P3948
// 题意：维护初始全为 0、长度为 n 的数组
// 先执行 opt 次操作：A L R X（区间加 X）或 Q L
// R（查询 [L, R] 中满足 min <= (T * i mod mod) <= max 的下标 i 数量
// 负数取模按 C++ 向 0 取整）；
// 之后无修改，再回答 Final 次区间查询 [L, R]。
// 数据范围：n <= 80000，opt <= 10^7，Final <= 10^7，opt 中的 Q 操作不超过 1000 次
// n, opt, mod, min, max, X 均在 int 范围内。
#include<bits/stdc++.h>
#define ll long long
// 算法标签：差分、前缀和
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
