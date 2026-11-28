// https://www.luogu.com.cn/problem/P5057
// 题意：维护长为 n 的初始全 0 数组，支持 m 次操作：
// 将区间 [L, R] 内 0/1 反转，或单点查询下标 i 的当前值。
// 数据范围：1 <= n <= 10^5，
// 1 <= m <= 5*10^5，L <= R。
// 难度评分：1600（洛谷分级换算）
// 算法标签：树状数组、差分
#include <bits/stdc++.h>
using namespace std;

int N, M, B[100001];

inline void A(int i) {
    for (; i <= N; i += i & -i)
        B[i] ^= 1;
}

inline int Q(int i) {
    int A = 0;
    for (; i; i -= i & -i)
        A ^= B[i];
    return A;
}

int main() {
	cin>>N>>M;
	while (M--) {
		int opt, l, r;
		cin>>opt>>l;
		if (opt == 1) A(l), scanf("%d", &r), A(r + 1);
		else printf("%d\n", Q(l));
	}
	return 0;
}
