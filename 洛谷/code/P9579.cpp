// https://www.luogu.com.cn/problem/P9579
// 题意：给定两个长度为 n 的数组 a, b。
// 构造正整数序列 p（设长度为 m）满足：p_1 = 1；
// 相邻两项差绝对值为 1（|p_i - p_{i+1}| = 1）；
// 对每个 1 <= k <= n，存在 1 <= i < j <= m 使得 p_i = a_k 且 p_j = b_k。
// 求 p 的最小可能长度 m。
// 题意：第一行输入 n，接下来 n 行输入 a_i, b_i；输出一个整数表示最小长度。
// 数据范围：1 <= n <= 5 * 10^5，1 <= a_i, b_i <= 10^9，a_i != b_i。
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
