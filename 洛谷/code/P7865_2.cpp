// https://www.luogu.com.cn/problem/P7865
// 题意：在 n * m 的矩形区域内给出 s 个覆盖矩形（左下角 (a1, b1)，右上角 (a2, b2)）
// 求这 s 个矩形的并是否完全覆盖后续给出的 L 个查询矩形（左下角 (r1, c1)，右上角 (r2, c2)）。
// 输入 n, m，然后 s 及 s 行覆盖矩形，再 L 及 L 行查询矩形。
// 输出 L 行，完全在并集内输出 Yes，否则输出 No。
// 数据范围：1 <= n, m <= 3*10^3，1 <= s, L <= 10^6，1 <= a1 < a2 <= n
// 1 <= b1 < b2 <= m，1 <= r1 < r2 <= n
// 1 <= c1 < c2 <= m（题面数据范围中写作 x1 < x2, y1 < y2）。
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 3000
int n;//行数
int m;//列数
int s;//无人机数
int l;//任务数
int a[max_n+2][max_n+2];//矩阵
bool ans;//答案
int main(){
	scanf("%d%d",&n,&m);
	memset(a,0,sizeof(a));
	scanf("%d",&s);
	for(register int i=1,x1,y1,x2,y2;i<=s;++i){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		++a[x1][y1];//左上
		++a[x2+1][y2+1];//右下
		--a[x2+1][y1];//左下
		--a[x1][y2+1];//右上
	}
	for(register int x=1;x<=n;++x){
		for(register int y=1;y<=m;++y){
			a[x][y]+=a[x-1][y]+a[x][y-1]-a[x-1][y-1];
		}
	}
	for(register int x=1;x<=n;++x){
		for(register int y=1;y<=m;++y){
			if(a[x][y])a[x][y]=1;
		}
	}
	for(register int x=1;x<=n;++x){
		for(register int y=1;y<=m;++y){
			a[x][y]+=a[x-1][y]+a[x][y-1]-a[x-1][y-1];
		}
	}
	scanf("%d",&l);
	for(register int i=1,x1,y1,x2,y2;i<=l;++i){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		if(a[x2][y2]-a[x1-1][y2]-a[x2][y1-1]+a[x1-1][y1-1]>=(x2-x1+1)*(y2-y1+1))puts("Yes");
		else puts("No");
	}
	return 0;
}
