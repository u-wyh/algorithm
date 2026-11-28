// https://www.luogu.com.cn/problem/P3138
// 题意：输入奶牛数 N，
// 以及每头牛的坐标 (x_i, y_i)（均为正奇数且互异）。
// 修建一条竖直线 x=a 和一条水平线 y=b（a, b 均为偶数），
// 将平面分成四个象限区域。
// 求如何选择 a 和 b，使四个区域中奶牛数量最多的那个区域牛数尽量小。
// 输出一个整数表示四个区域最大牛数的最小值。
// 数据范围：1 <= N <= 1000，
// 1 <= x_i, y_i <= 10^6（正奇数）。
// 难度评分：1200（洛谷分级换算）
// 算法标签：离散化、二维前缀和、枚举
#include<bits/stdc++.h>
using namespace std;
#define MAXN 100005
#define LL long long
#define INF 1e9
#define MOD 1000000007

const int L=1005;
struct node{
	LL int s,num;
};
node zx[L],zy[L];
bool cmp(const node &b,const node &c){
	return b.s<c.s;
}
LL int n,x[L],y[L],ans=INF,sum[L][L];

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>zx[i].s,cin>>zy[i].s;
		zx[i].num=i;
		zy[i].num=i;
	}
	sort(zx+1,zx+n+1,cmp);
	sort(zy+1,zy+n+1,cmp);
	for(int i=1;i<=n;i++){
		x[zx[i].num]=i;
		y[zy[i].num]=i;
	}//离散化
	for(int i=1;i<=n;i++)
		sum[x[i]][y[i]]++;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];//预处理部分
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			ans=min(ans,max(max(sum[i][j],sum[i][n]-sum[i][j]),max(sum[n][j]-sum[i][j],sum[n][n]-sum[n][j]-sum[i][n]+sum[i][j])));//四个象限
	printf("%lld",ans);
	return 0;
}
