// https://www.luogu.com.cn/problem/P6510
// 题意：给定从左到右 N 头奶牛的身高 h_i，求最长的连续子段
// 使得最左端奶牛 A 最矮、最右端奶牛 B 最高（B > A 且中间奶牛身高与 A, B 均不同），输出最多奶牛数（无解输出 0）。
// 数据范围：2 <= N <= 10^5，1 <= h_i < 2^31。
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100005;

int n, ans, tx, tn;
int a[maxn], sx[maxn], sn[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%d", a + i);
  for (int i = 1; i <= n; ++i) {
    while (tn && a[sn[tn]] >= a[i]) --tn;
    while (tx && a[sx[tx]] < a[i]) --tx;
    int k = upper_bound(sn + 1, sn + 1 + tn, sx[tx]) - sn;
    if (k != (tn + 1)) {
      ans = max(ans, i - sn[k] + 1);
    }
    sn[++tn] = i;
    sx[++tx] = i;
  }
  printf("%d\n", ans);
  return 0;
}
