#include<bits/stdc++.h>
#define mod 1000000007//模数
using namespace std;
const int N=1e6+10;
int n,m;
long long dp[N][2];//记得开long long
vector<int> vec[N];
void dfs(int cur,int fa){//因为是无向边，需要记录它的父亲以避免重复
	for(int i=0;i<vec[cur].size();i++){
		int to=vec[cur][i];
		if(to==fa)//判断父亲
			continue;
		dfs(to,cur);//先搜索，再转移，不然dp[to][0/1]还没有算出来，转移无效
		dp[cur][0]=(dp[cur][0]*(dp[to][0]+m*dp[to][1]%mod))%mod;
		dp[cur][1]=(dp[cur][1]*(dp[to][0]+(m-1)*dp[to][1]%mod))%mod;//状态转移
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		vec[u].push_back(v);
		vec[v].push_back(u);//记得存双向边
	}
    for(int i=1;i<=n;i++)
        dp[i][0]=dp[i][1]=1;//初始状态
	dfs(1,0);//从根结点深搜
	cout<<(dp[1][0]+m*dp[1][1]%mod)%mod;//答案
	return 0;
}
