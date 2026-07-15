#include <stdio.h>
#include <limits.h>

#define N 100005
#define INF 1000000000

int f[N + 5], v[N + 5], n, b, u, now, ans;

// 实现min函数
int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d", &n, &b);
    for (int i = 0; i <= N; i++) {
        f[i] = INF;
    }
    f[0] = 0;

    for (int i = 1; i <= b; i++) {
        scanf("%d", &v[i]);
        for (int j = v[i]; j <= N; j++) {
            f[j] = min(f[j], f[j - v[i]] + 1);
        }
    }

    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        x -= now;
        now += x;
        // 如果now为0，则不减少步数
        if (now > 0) {
            now--;
        }
        if (x < 0) {
            printf("-1");
            return 0;
        }
        if (f[x] == INF) {
            printf("-1");
            return 0;
        }
        ans += f[x];
    }

    printf("%d", ans);
    return 0;
}
