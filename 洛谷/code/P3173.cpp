// https://www.luogu.com.cn/problem/P3173
// 题意：输入矩形巧克力的长宽格子数 n, m，n-1 条横线的单刀切割代价 y_1..y_{n-1}
// 以及 m-1 条竖线的单刀切割代价 x_1..x_{m-1}。
// 每次沿着已有切块上的一条横线或竖线将当前所在块一分为二，切割代价只与所沿的横/竖线编号有关（与当前块长度无关），直到切出全部 n*m 个单位块。
// 输出将整块巧克力切成 n*m 块的最小总代价。
// 数据范围：n <= 10000，m <= 10000。
#include<iostream>
#include<cstdio>
// 算法标签：贪心、数学
using namespace std;
size_t a[10010],b[10010],sum=0,n,m;
int main() {
	cin>>n>>m;
	n--,m--;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>b[i];
		sum+=b[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			sum+=min(a[i],b[j]);
		}
	}
	cout<<sum<<endl;
	return 0;
}
