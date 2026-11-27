// https://www.luogu.com.cn/problem/P1430
// 题意：有多组测试数据，每组给出一个长为 n 的整数序列。
// A 和 B 轮流从序列左端或右端取至少一个数，但单次不能两端都取。
// A 先取，取完所有数后各自得分为所取数之和。
// 双方都足够聪明且最大化自己得分，输出每组中 A 的最终得分。
// 数据范围：
// T <= 100（测试数据组数）
// n <= 1000（序列长度，序列元素范围题面未写明）
#include<bits/stdc++.h>
// 算法标签：区间动态规划、博弈论、前缀和
using namespace std;

int d[1010],dp[1010][1010];
int p[1010][1010],q[1010][1010];

int main()
{
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
            scanf("%d",&d[i]);
		for(int i=1;i<=n;i++)
            d[i]=d[i-1]+d[i];//前缀和
		for(int len=1;len<=n;len++){
			for(int i=1;i<=n-len+1;i++){
			    int j=i+len-1;
				dp[i][j]=d[j]-d[i-1]-min(0,min(p[i][j-1],q[i+1][j]));//状态转移
				p[i][j]=min(p[i][j-1],dp[i][j]);
                q[i][j]=min(q[i+1][j],dp[i][j]);//更新
			}
		}
		printf("%d\n",dp[1][n]);//输出答案
	}
	return 0;
}
