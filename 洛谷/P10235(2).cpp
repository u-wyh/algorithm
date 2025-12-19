#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

#define lowbit(x) x & -x
using namespace std;

const int N = 100010;

int T, n, k;
int a[N], c[N];
int nums[N];
int tt;
int fnd[N];

int find(int x) {
	return lower_bound(nums + 1, nums + tt + 1, x) - nums;
}

int ask(int x) {
	int res = 0;
	for(; x; x -= lowbit(x)) res += c[x];
	return res;
}

void add(int x, int y) {
	for(; x <= n; x += lowbit(x)) c[x] += y;
}

bool check(long long limit) {
	int cnt = 1; //段数
	long long f = 0; //目前处理的段的逆序对数
	int L = 1; //目前处理的段的左端点
	for(int i = 1; i <= n; i++) {
		int tmp = ask(tt) - ask(fnd[i]); //计算新增的逆序对数
		if(f + tmp > limit) {
			cnt++; //段数 + 1
			f = 0; //重置逆序对数
			for(int j = L; j <= i - 1; j++)
				add(fnd[j], -1); //清除上一区间的贡献
			L = i; //更新左端点
		}
		else f += tmp;
		add(fnd[i], 1); //加入树状数组
	}
	for(int i = L; i <= n; i++) add(fnd[i], -1); //不要忘了最后一段也要抹去
	return cnt > k;
}

int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &k);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			nums[++tt] = a[i];
		}
		sort(nums + 1, nums + tt + 1);
		tt = unique(nums + 1, nums + tt + 1) - nums - 1;
		for(int i = 1; i <= n; i++) fnd[i] = find(a[i]);
		long long l = 0, r = 1e10;
		while(l < r) {
			long long mid = l + r >> 1;
			if(check(mid)) l = mid + 1;
			else r = mid;
		}
		printf("%lld\n", l);
		for(int i = 1; i <= tt; i++) nums[i] = 0;
		tt = 0;
	}
	return 0;
}
