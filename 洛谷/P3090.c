#include <stdio.h>

#define int long long

#define N 3000000

int n;
int ans[N];
int x, y, a, b, k;

int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int main() {
    n = read();
    k = read();
    while (k--) {
        x = read();
        y = read();
        a = read();
        b = read();
        for (int i = 1; i <= y; i++) {
            ans[(a * i + b) % n] += x;
        }
    }
    for (int i = 0; i < n; i++) {
        if (ans[i] > 0) {
            ans[(i + 1) % n] += ans[i] - 1;
            ans[i] = 1;
        }
    }
    while (ans[0] > 1) {
        for (int i = 0; i < n; i++) {
            if (ans[i] > 0) {
                ans[(i + 1) % n] += ans[i] - 1;
                ans[i] = 1;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (ans[i] == 0) {
            printf("%lld\n", i);
            return 0;
        }
    }
    return 0;
}
