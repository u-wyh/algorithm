#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int n, k;
double a[10005];
double l, r, mid;
char s[100];

int check(double x) {
    int tot = 0;
    for (int i = 0; i < n; i++) { // 注意数组索引从0开始
        tot += floor(a[i] / x);
    }
    return tot >= k;
}

int main() {
    scanf("%d%d", &n, &k);
    r = 0.0; // 初始化r为0.0
    for (int i = 0; i < n; i++) { // 注意数组索引从0开始
        scanf("%lf", &a[i]);
        r += a[i]; // 累加所有a[i]的值到r
    }
    l = 0.0; // 初始化l为0.0，因为我们要找的是正数解
    while (r - l > 1e-4) {
        mid = (l + r) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    // 使用snprintf来格式化字符串，避免直接使用strlen和字符串操作
    snprintf(s, sizeof(s), "%.3f", l);
    printf("%s\n", s); // 输出结果
    return 0;
}
