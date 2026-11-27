// https://www.luogu.com.cn/problem/P9102
// 题意：有 n 袋糖，第 i 袋有 a_i 颗糖。
// 求有多少个非空袋子子集 S，使得对于任意整数 y in [1, sum_{i in S} a_i]，都能从 S 中选出若干整袋使其糖果总数恰好为 y。
// 答案对 10^9+7 取模。
// 数据范围：1 <= n <= 5000，1 <= a_i <= 5000。
// 算法标签：动态规划、排序
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=5e3+5,mod=1e9+7;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return x*f;
}
int n,a[N],f[N],ans;
signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	f[0]=1;
	for(int i=1;i<=n;i++)
		for(int j=N-5;j>=a[i]-1;j--)
			f[min(j+a[i],N-5)]+=f[j],f[min(j+a[i],N-5)]%=mod;
	for(int i=1;i<=N-5;i++)ans=(ans+f[i])%mod;
	printf("%d",ans);
	return 0;
}
