// https://www.luogu.com.cn/problem/P9583
// 题意：n 行 m 列方格纸初始全空白，共 q 次涂色操作：op = 1 将第 x 行所有格子加 1 层颜色
// op = 2 将第 x 列所有格子加 1 层颜色。
// 每次涂色结束后，所有恰好达到 k 层的格子颜色会被擦掉变为空白（后续可再涂）。
// 求最终有多少个非空白方格。
// 题意：第一行输入 n, m, q, k，接下来 q 行输入 op, x；输出一个整数。
// 数据范围：1 <= n, m <= 2 * 10^5，1 <= k <= q <= 5 * 10^5，op ∈ {1, 2}。
#include<bits/stdc++.h>
using namespace std;

long long n,m,nm,k,as,x,h[200010],s[200010],ans=0,c,ss[500010];

int main()
{
	cin>>n>>m>>nm>>k;
	ss[0]=n;
	for(int i=1;i<=nm;i++)
	{
		cin>>as>>x;
		if(as==1) {
			h[x]++;
			ss[h[x]-1]--;//涂过h[x]-1次的行数减1
			ss[h[x]]++;//涂过h[x]次的行数加1
		}
		else
            s[x]++;
	}
	sort(h+1,h+n+1);//从小到大排序
	ans=n*m;//答案初始化
	for(int i=1;i<=m;i++){
		c=s[i]%k;
		for(int j=(k-c)%k;j<=h[n];j+=k){
			ans=ans-ss[j];
		}
	}
	cout<<ans;

	return 0;
}
