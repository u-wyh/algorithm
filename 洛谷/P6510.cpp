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
