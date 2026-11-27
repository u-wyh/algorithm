// https://www.luogu.com.cn/problem/P1725
// 题意：从 0 号格子出发，每次向右跳 L 到 R 格，
// 落在编号大于 N 的位置就结束。
// 每次落在河中的格子 i 得到 A_i，求过河能获得的最大总和。
// 数据范围：1 ≤ L ≤ R ≤ N ≤ 2×10^5，A_0=0，
// −1000 ≤ A_i ≤ 1000，答案 ≤ 2^31−1。
// 算法标签：动态规划、单调队列

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
