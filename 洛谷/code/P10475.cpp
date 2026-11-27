// https://www.luogu.com.cn/problem/P10475
// 题意：给 R 行 C 列的大写字母网格，找一个最小的矩形块，横向和纵向重复它就能铺出原网格。最后一排或一列块可以裁掉超出的部分，输出矩形块的最小面积。
// 数据范围：1 ≤ R ≤ 10000，1 ≤ C ≤ 75，格子是大写英文字母。
// 算法标签：字符串哈希、KMP

#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
const int N = 10005, p = 131, M = 75;
int r, c, a[N], b[M], nxt[N], ans, ans2, j;
string s[N];
signed main(){
	cin >> r >> c;
	for(int i = 1; i <= r; i++){
		cin >> s[i];
		s[i] = " " + s[i];
		for(int j = 1; j <= c; j++){
			a[i] = a[i] * p + s[i][j];
		}
	}
	for(int i = 1; i <= c; i++){
		for(int j = 1; j <= r; j++){
			b[i] = b[i] * p + s[j][i];
		}
	}
	nxt[1] = 0;
	j = 0;
	for(int i = 2; i <= r; i++){
		while(j && a[i] != a[j + 1]) j = nxt[j];
		if(a[i] == a[j + 1]) j++;
		nxt[i] = j;
	}
	ans = r - nxt[r];
	nxt[1] = 0;
	j = 0;
	for(int i = 2; i <= c; i++){
		while(j && b[i] != b[j + 1]) j = nxt[j];
		if(b[i] == b[j + 1]) j++;
		nxt[i] = j;
	}
	ans2 = c - nxt[c];
	cout << ans * ans2;
	return 0;
}
