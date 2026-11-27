// https://www.luogu.com.cn/problem/P4090
// 题意：第一行输入奶牛数量 N，第二行输入 N 个整数 c_1..c_N；
// 初始按 1..N 从队首到队尾排队，每次队首奶牛拿一份礼物后插到队尾 c_i 头奶牛之前。
// 无限次发礼物后，求无论发多少份礼物都永远收不到任何礼物的奶牛数量。
// 输出一个整数表示答案。
// 数据范围：1 <= N <= 10^5，0 <= c_i <= N-1。
#include<bits/stdc++.h>
// 算法标签：二分答案、贪心、排序
using namespace std;
const int N=1e5+5;

int read()
{
	int s=0;
	char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x<10) putchar(x+'0');
	else
	{
		write(x/10);
		putchar(x%10+'0');
	}
}
void print(int x,char c='\n')
{
	write(x);
	putchar(c);
}
int a[N],b[N],n;
bool check(int now)
{
    //因为题目给出的位置是从后往前数的，所以这里的位置都是以从最后一个向前的若干个的形式表示
	for (int i=1;i<now;i++) b[i]=a[i];
	sort(b+1,b+now);
	int tmp=n-now;//牛1437的位置
	for (int i=1;i<now;i++)
	{
		if (b[i]>tmp) return 0;
		tmp++;
	}
	return 1;
}

signed main()
{
	n=read();
	for (int i=1;i<=n;i++) a[i]=read();
	int l=1,r=n;
	while (l<=r)
	{
		int mid=(l+r)/2;
		if (check(mid)) l=mid+1;
				   else r=mid-1;
	}
	print(n-r);

	return 0;
}