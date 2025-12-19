#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long n, tot, a[1000000];

int compare(const void *a, const void *b) {
    long long arg1 = *((long long*)a);
    long long arg2 = *((long long*)b);
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

void dfs(long long x) {
    if (x > 9e17) return;  // 提前返回以避免超出范围
    a[++tot] = x;
    for (int i = 0; i <= 1; i++) {
        dfs(x * 10 + i);
    }
}

int main() {
    scanf("%lld", &n);
    dfs(1);
    qsort(a + 1, tot, sizeof(long long), compare);
    for (int i = 1; i <= tot; i++) {
        if (a[i] % n == 0) {
            printf("%lld\n", a[i] / n);
            return 0;
        }
    }
    printf("No Solution\n");
    return 0;
}
