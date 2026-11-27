// https://www.luogu.com.cn/problem/P3608
// 题意：输入奶牛数 N，以及一排从左到右各头奶牛互不相同的身高 h_1..h_N。
// 设第 i 头奶牛左边比它高的牛有 L_i 头、右边比它高的牛有 R_i 头
// 若 max(L_i, R_i) > 2 * min(L_i, R_i) 则称第 i 头奶牛不平衡。
// 输出不平衡的奶牛总数。
// 数据范围：1 <= N <= 10^5，0 <= h_i <= 10^9，所有 h_i 互不相同。
#include<bits/stdc++.h>
// 算法标签：树状数组、排序
using namespace std;
typedef long long ll;
const int N = 1000005;
struct sCow
{
	int iH, iBh;
}Cow[N];
bool cmp(sCow x, sCow y){return x.iH > y.iH;}
int iSum[N], n;
int lowbit(int x) {return x & -x;}
void Add(int x, int k){for(; x <= n; x += lowbit(x)) iSum[x] += k;}
int Query(int x){int ans = 0;for(; x; x -= lowbit(x)) ans += iSum[x];return ans;}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &Cow[i].iH), Cow[i].iBh = i;
	sort(Cow + 1, Cow + 1 + n, cmp);
	int iAns = 0;
	for(int i = 1; i <= n; i++)
	{
		Add(Cow[i].iBh, 1);
		int l = Query(Cow[i].iBh - 1);
		int r = i - l - 1;
		if(max(l, r) > 2 * min(l, r)) iAns++;
	}
	cout<<iAns;
}
