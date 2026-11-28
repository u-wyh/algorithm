// https://www.luogu.com.cn/problem/P4378
// 题意：给定长度为 N 的数组 A，
// 模拟每轮先输出 "moo" 再单向从左到右冒泡一遍的标准冒泡排序，
// 求 "moo" 的输出次数。
// 数据范围：1 <= N <= 100000，
// 0 <= A[i] <= 10^9（元素可重复）。
// 难度评分：1400（洛谷分级换算）
// 算法标签：树状数组、离散化
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
