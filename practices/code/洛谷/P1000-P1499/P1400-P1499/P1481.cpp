// https://www.luogu.com.cn/problem/P1481
// 题意：给一个单词表，挑选并排列一些词，使除最后一个外每个词都是下一个词的前缀。
// 求最长词链包含的单词数。
// 数据范围：1 ≤ N ≤ 2000，每词长 1 到 75，只含小写字母，
// 单词按字典序输入且无重复。
// 难度评分：1100（洛谷分级换算）
// 算法标签：动态规划、字符串

#include<bits/stdc++.h>
using namespace std;
char s[2010][80];
int f[2010],n,ans;
int main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
		f[i]=1;
		for(int j=i-1;j>=1;j--)
			if(strstr(s[i],s[j])==s[i])
				f[i]=max(f[j]+1,f[i]);
		ans=max(f[i],ans);
	}
	cout<<ans;
	return 0;
}
