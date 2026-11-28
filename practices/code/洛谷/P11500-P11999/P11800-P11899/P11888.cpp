// https://www.luogu.com.cn/problem/P11888
// 题意：
// 共 t 组询问，每组给定正整数 n 和 m。
// 记斐波那契数列 f_1 = f_2 = 1，
// f_i = f_{i-1} + f_{i-2}。
// 求所有满足 1 <= a_1, ...,
// a_n <= m 的元组对应的
// lcm(f_{a_1}, ..., f_{a_n}) 之乘积。
// 每组输出一行答案，对 37426667 取模。
// 数据范围：
// 1 <= t <= 300
// 1 <= n <= 2 * 10^{17}
// 1 <= m <= 2 * 10^7
// 难度评分：2300（洛谷分级换算）
// 算法标签：动态规划
#include<bits/stdc++.h>
#define int long long
using namespace std;
int c;
int v[15],dp[100005][15],a[100005];
int p10[15]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
void mian(){
	string n;cin>>n;int l=n.length();
	for(int i=0;i<l;i++)a[i+1]=n[i]-'0';
	for(int i=1;i<=9;i++)cin>>v[i];
	memset(dp,0,sizeof dp);
	int s=0;
	for(int i=1;i<=l;i++)s+=v[a[i]];
	for(int i=l;i>=1;i--){
		for(int j=1;j<=min(9ll,l-i+1);j++){
			dp[i][j]=max(dp[i+1][j],dp[i+1][j-1]+v[a[i]]-p10[j-1]*a[i]);
		}
	}
	int ans=0;
	for(int i=1;i<=9;i++)ans=max(ans,dp[1][i]);
	cout<<s-ans<<endl;
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>c;
	int t;cin>>t;
	while(t--)mian();
	return 0;
}
