// https://www.luogu.com.cn/problem/P4623
// 题意：给定平面上 N 个不共线三点构成的三角形，
// 以及 M 条平行于坐标轴的直线 x = c 或 y = c
// 求每条直线各穿过多少个三角形（穿过指将三角形分成两个面积大于 0 的多边形）。
// 数据范围：2 <= N, M <= 10^5，
// 0 <= x_1, y_1, x_2, y_2, x_3,
// y_3 < 10^6。
// 难度评分：900（洛谷分级换算）
// 算法标签：差分、前缀和
#include<bits/stdc++.h>
using namespace std;
const int N=1000010;

inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch >'9'){
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}

int X[N],Y[N],n,m,mx1,mx2;
int main()
{
	n=read();
	while(n--){
		int a=N,b=0,c=N,d=0;
		for(int i=1;i<=3;i++){
			int x=read(),y=read();
			a=min(a,x),b=max(b,x),c=min(c,y),d=max(d,y);
			mx1=max(mx1,x),mx2=max(mx2,y);
		}
		X[a+1]++,X[b]--,Y[c+1]++,Y[d]--;
	}
	for(int i=0;i<=mx1+1;i++)X[i]+=X[i-1];
	for(int i=0;i<=mx2+1;i++)Y[i]+=Y[i-1];
	m=read();
	while(m--){
		char s;
		cin>>s;
		int x=read();
		if(s=='x')printf("%d\n",X[x]);
		if(s=='y')printf("%d\n",Y[x]);
	}
	return 0;
}
