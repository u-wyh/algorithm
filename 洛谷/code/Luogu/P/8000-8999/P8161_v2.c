#include <stdio.h>
#include <stdlib.h>

#define N 300007

int n;
long long m;
long long a[N], b[N];

int check(long long lim) {
    long long s = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i] * m >= lim) {
            s += (a[i] * m - lim) / a[i]; // 多余的
        } else {
            // 注意这里要加上b[i]-1来确保向上取整
            s -= (lim - a[i] * m + b[i] - 1) / b[i]; // 缺少的
        }
    }
    return s >= 0;
}

int main() {
    scanf("%d %lld", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
    }
    int mx = 0;
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &b[i]);
        a[i] = (a[i] > b[i]) ? a[i] : b[i]; // 使用三元运算符简化
        mx = (a[i] > mx) ? a[i] : mx; // 更新最大值
    }
    long long l = 0, r = (long long)mx * m;
    while (l <= r) {
        long long mid = l + (r - l) / 2;
        if (check(mid)) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    printf("%lld\n", l - 1); // 因为循环结束时l已经超出了答案，所以要减1
    return 0;
}
