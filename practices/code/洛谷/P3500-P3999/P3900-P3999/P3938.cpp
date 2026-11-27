// https://www.luogu.com.cn/problem/P3938
// 题意：兔子按斐波那契模型繁衍
// （每对兔子从出生后第二个月起
// 每月月初生一对新兔子，按出生顺序编号，
// 同月出生则父母编号小的优先编号，
// 1 号兔子为祖先）。
// 给出 m 组询问 (a_i, b_i)，
// 求编号为 a_i 和 b_i 的两对兔子的最近公共祖先编号。
// 数据范围：
// 测试点 10 中 m = 300010（各测试点 m 最大为 300010），
// a_i, b_i <= 10^12。
// 算法标签：LCA、二分查找、斐波那契数列
#include<bits/stdc++.h>
using namespace std;
long long n, a, b;
long long f[100];
int main() {
	cin>>n;
	f[0] = 1;
	f[1] = 1;
	for(int i = 2; i <= 59; i++)
		f[i] = f[i - 1] + f[i - 2];
	for(int i = 1; i <= n; i++) {
		scanf("%lld %lld", &a, &b);
		while(a != b) {
			if(b < a) {
				long long k = a;
				a = b;
				b = k;
			}
			int l = 1, r = 59;
			while(l <= r) {
				int mid = (l + r) / 2;
				if(f[mid] < b)
				    l = mid + 1;
				else
				    r = mid - 1;
			}
			b -= f[l - 1];
		}
		printf("%lld\n", a);
	}
	return 0;
}
