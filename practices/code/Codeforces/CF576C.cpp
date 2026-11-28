// https://codeforces.com/problemset/problem/576/C
// 题意：平面上 n 个整点 (x_i, y_i)，重排它们的访问顺序。
// 规则：要求相邻两点曼哈顿距离之和不超过 2.5*10^9。
// 输出：一行 n 个整数表示合法的点编号排列。
// 数据范围：1 <= n <= 10^6，
// 0 <= x_i, y_i <= 10^6。
// 难度评分：2100（CF 官方）
// 算法标签：分块、排序
#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e6+10;
int n,block;
struct node
{
	int l,r,id,b;
}que[MAXN];

int read()
{
	int sum=0,fh=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fh=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {sum=(sum<<3)+(sum<<1)+(ch^48);ch=getchar();}
	return sum*fh;
}

bool cmp(const node &fir,const node &sec)
{
	if(fir.b!=sec.b) return fir.b<sec.b;
	if(fir.b&1) return fir.r<sec.r;
	return fir.r>sec.r;
}

int main()
{
	n=read();block=1000;//此处设块长为 1000，无需担心被上述反例卡掉（各位读者可以自行计算是否会被卡掉）
	for(int i=1;i<=n;i++) {que[i].l=read();que[i].r=read();que[i].id=i;que[i].b=(que[i].l-1)/block+1;}
	sort(que+1,que+n+1,cmp);
	for(int i=1;i<=n;i++) cout<<que[i].id<<" ";
	cout<<"\n";
	return 0;
}
