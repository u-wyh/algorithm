// https://www.luogu.com.cn/problem/P1950
// 题意：给定 n 行 m 列的网格，点号是空白，星号是已涂画的位置。
// 沿格子边界选出一个非空矩形，要求内部全是空白。求不同矩形的数量。
// 数据范围：1 ≤ n,m ≤ 1000。
// 难度评分：1300（洛谷分级换算）
// 算法标签：单调栈

#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

inline int read() {
	char c = getchar();
	int x = 0, f = 1;
	for( ; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for( ; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
	return x * f;
}

const int N = 1e3 + 11;

int n, m, h[N][N], st[N], l[N], r[N], top = 0;
char a[N][N];
long long ans;

inline void work(int x) {
	top = 0;
	for(int i = 1; i <= m; ++i) {
		while(top && h[x][st[top]] >= h[x][i]) {
			r[st[top--]] = i;
		}
		st[++top] = i;
	}
	while(top) r[st[top--]] = m + 1;
	for(int i = m; i >= 1; --i) {
		while(top && h[x][st[top]] > h[x][i]) {
			l[st[top--]] = i;
		}
		st[++top] = i;
	}
	while(top) l[st[top--]]=0;
}

int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++)
        scanf("%s", a[i] + 1);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(a[i][j] == '*')
                h[i][j] = 0;
			else
                h[i][j] = h[i - 1][j] + 1;
		}
	}
	for(int i = 1; i <= n; i++) {
		work(i);
		for(int j = 1; j <= m; j++) {
			ans += (j - l[j]) * (r[j] - j) * h[i][j];
		}
	}
	cout << ans << '\n';
	return 0;
}
