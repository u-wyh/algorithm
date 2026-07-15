#include <stdio.h>
#include <ctype.h>

#define ll long long

int read() {
    int x = 0, f = 1;
    char ch = 0;
    while (!isdigit(ch)) {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

#define maxN 100005

int T, n;
ll ans;
int L[maxN], R[maxN];

int cal(int x, int i) {
    if (!((x >> i) & 1))
        x = ((x >> i) | 1) << i;
    return x;
}

int main() {
    T = read();
    while (T--) {
        ans = 0;
        n = read();
        for (int i = 1; i <= n; i++) {
            L[i] = read();
            R[i] = read();
        }
        for (int i = 30; i >= 0; i--) {
            ll d = 1ll << i;
            int flag = 0;
            for (int j = 1; j <= n; j++) {
                if (cal(L[j], i) > R[j]) {
                    flag = 1;
                    break;
                }
            }
            if (flag)
                continue;
            for (int j = 1; j <= n; j++) {
                L[j] = cal(L[j], i);
            }
            ans |= d;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
