#include <stdio.h>
#include <stdlib.h>

#define INF 2000000000
#define N 105

int n, ans;
int a[N], to[N], cnt[N];

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    qsort(a+1, n, sizeof(int), compare);

    a[n+1] = INF;
    a[0] = -INF;  // 注意：由于C语言的数组是从0开始的，所以这里稍微调整

    for (int i = 1; i <= n; i++) {
        if (a[i] - a[i - 1] > a[i + 1] - a[i]) {
            to[i] = i + 1;
            cnt[i + 1]++;
        } else {
            to[i] = i - 1;
            cnt[i - 1]++;
        }
    }

    // 初始化ans
    ans = 0;

    // 找出不能通过传球得到球的奶牛
    for (int i = 1; i <= n; i++) {
        if (cnt[i] == 0) {
            ans++;
        }
    }

    // 找出相互传球的奶牛对
    for (int i = 1; i < n; i++) {
        if (cnt[i] == 1 && cnt[i + 1] == 1 && to[i] == i + 1 && to[i + 1] == i) {
            ans++;
        }
    }

    printf("%d\n", ans);
    return 0;
}
