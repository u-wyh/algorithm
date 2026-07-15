#include<bits/stdc++.h>
using namespace std;

const int N=2e5+86;

int n,dp[N],l,r,ans=-0x3f3f3f3f,v[N],dq[N],h=1,t=0;
//有负数所以 ans 初始化为负无穷
int main()
{
    memset(dp,-1e9,sizeof(dp));
	scanf("%d%d%d",&n,&l,&r);
	if(l>r) swap(l,r); //鲁棒性
	for(int i=0;i<=n;i++)
		scanf("%d",&v[i]);
	for(int i=l;i<=n;i++)
	{
		while(h<=t&&dq[h]<i-r) h++;
		while(h<=t&&dp[dq[t]]<dp[i-l]) t--;
		dq[++t]=i-l;
		dp[i]=dp[dq[h]]+v[i];
		if(i+r>n)
			ans=max(dp[i],ans);
	}
	printf("%d\n",ans);
	return 0;
}
