#include <stdio.h>
#include <stdlib.h>

#define LL long long
#define N 10000005

LL f[N];
LL w, c, n, m;

int main() {
    int i;
    scanf("%lld %lld", &m, &n);  // 读取m和n

    // 初始化f数组为0（可选，如果数组在全局作用域定义，则自动初始化为0）
    for (i = 0; i <= m; i++) {
        f[i] = 0;
    }

    while (n--) {
        scanf("%lld %lld", &w, &c);  // 读取w和c
        for (i = w; i <= m; i++) {
            f[i] = (f[i] > f[i - w] + c) ? f[i] : f[i - w] + c;
        }
    }

    printf("%lld\n", f[m]);  // 输出f[m]

    return 0;
}
