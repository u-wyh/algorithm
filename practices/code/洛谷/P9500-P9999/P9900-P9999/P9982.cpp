// https://www.luogu.com.cn/problem/P9982
// 题意：数轴上有 N 座谷仓分别位于整点 x_1..x_N。
// Q 次相互独立的询问，每次给出 (a_i, b_i)：
// 需选择一个整点 y（0 <= y <= 10^6）放置所有干草堆再分别运往各谷仓
// 运往位于 x 的谷仓时若 y > x 则浪费 a_i * (y - x)，
// 若 x > y 则浪费 b_i * (x - y)（x = y 为 0）。
// 求最优选择 y 时被浪费的干草堆总数的最小值。
// 题意：第一行输入 N，第二行输入 x_1..x_N，第三行输入 Q，
// 后 Q 行每行输入 a_i, b_i；输出 Q 行整数。
// 数据范围：1 <= N <= 2 * 10^5，
// 0 <= x_i <= 10^6，1 <= Q <= 2 * 10^5
// 1 <= a_i, b_i <= 10^6。
// 难度评分：1300（洛谷分级换算）
// 算法标签：排序、前缀和
#include<bits/stdc++.h>
using namespace std;

#define MAXN 200005

int n,q,u;
long long x[MAXN],sum[MAXN];
long long a,b;

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i];
	}	
	sort(x+1,x+n+1);
   
	for(int i=1;i<=n;i++){ 
		sum[i]=sum[i-1]+x[i];
	}
   
	cin>>q;
	for(int i=1;i<=q;i++){
		cin>>a>>b;
		u=(int)(ceil((long double)b*n/(a+b))); 
		cout<<(x[u]*(u)-sum[u])*a+(sum[n]-sum[u]-x[u]*(n-u))*b<<endl;
	}
	
	return 0;
}