#include <stdio.h>
#include <stdlib.h>

int n, m;
long long K, l, r = 2e9, mid, A[100005], B[100005];

int cmp(const void *a,const void *b){
    return (*(long long  *)a - *(long long *)b);
}
// 判断小于等于当前 mid 的 C[i] = A[i] + B[j] 的个数是否小于 K
int check() {
    long long cnt = 0;
    for (int i = 1; i <= n; ++i) {
        int j;
        for (j = 1; j <= m; ++j) {
            if (B[j] > mid - A[i]) break; // 找到第一个大于 mid - A[i] 的 B[j]
        }
        cnt += j - 1; // 累加小于等于 mid - A[i] 的 B[j] 个数
    }
    return cnt < K;
}

int main() {
    scanf("%d%d%lld", &n, &m, &K);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &A[i]);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%lld", &B[i]);
    }
    qsort(B + 1, m, sizeof(long long), cmp);
    while (l < r) {
        mid = l + (r - l) / 2; // 防止溢出
        if (check()) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    printf("%lld", l);
    return 0;
}
