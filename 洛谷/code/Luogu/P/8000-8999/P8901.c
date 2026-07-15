#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define N 100010
#define M 5000010

int T, n, x, cnt, ans, mx[4], v[M+10], vis[M+10], prime[M];

void get_prime(int n) {
    vis[1] = 1;
    mx[1] = 1;
    v[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            prime[++cnt] = i;
            mx[i % 4] = i;
        }
        for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
            vis[i * prime[j]] = 1;
            if (!(i % prime[j])) {
                break;
            }
        }
        v[i] = !(i % 4) ? i / 2 : (i - mx[i % 4]) / 2 + 1;
    }
}

int main() {
    scanf("%d", &T);
    get_prime(M);
    while (T--) {
        scanf("%d", &n);
        ans = INT_MAX;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &x);
            if (v[x] / 2 < ans / 2)
                ans = v[x];
        }
        if (ans & 1) {
            printf("Farmer John\n");
        } else {
            printf("Farmer Nhoj\n");
        }
    }
    return 0;
}
