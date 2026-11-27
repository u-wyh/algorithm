// https://www.luogu.com.cn/problem/P6824
// 题意：给定长为 n 的正整数序列 a 和整数 k，
// 选择一个非负整数 x 使得
// 满足 (a_i xor x) <= k 的 i 个数尽量多，求这个最大值。
// 数据范围：1 <= n, k, a_i <= 10^6。
// 算法标签：差分、前缀和、位运算
#include<bits/stdc++.h>
using namespace std;

const int M=1e6+10;
int c[M*2],a[M],n,k,ans,maxn;
int s1[50],s2[50];

void f(int b)
{
	memset(s1,0,sizeof(s1));
	memset(s2,0,sizeof(s2));
	int len1=0,len2=0,kk=k;
	while(b)
		s1[++len1]=b%2,b/=2;
	while(kk)
		s2[++len2]=kk%2,kk/=2;
	int len=max(len1,len2);
	for (int i=1;i<=len/2;i++)
		swap(s1[i],s1[len-i+1]),swap(s2[i],s2[len-i+1]);
	int sum=0;
	for (int i=1;i<=len;i++)
		if (s2[i]==0)
			sum=sum*2+s1[i];
		else
		{
			int k1=(sum*2+s1[i])*1<<(len-i),k2=(sum*2+1+s1[i])*1<<(len-i);
			c[k1]++,c[k2]--;
			sum=sum*2+(s1[i]^1);
		}
	c[sum]++,c[sum+1]--;
}

int main()
{
	scanf("%d%d",&n,&k);
	maxn=k;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		f(a[i]);
		maxn=max(maxn,a[i]);
	}
	for (int i=1;i<=maxn*2;i++)
		c[i]+=c[i-1];
	for (int i=0;i<=maxn*2;i++)
		ans=max(ans,c[i]);
	cout<<ans;
	return 0;
}
