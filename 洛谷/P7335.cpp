#include<bits/stdc++.h>
#define N 3005
using namespace std;

int read() {
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return x * f;
}

int n, k, a[N], mx[N][N], num[N];
long long f[N][2];

struct len {
    int l, r, w;
} s[N][N];

signed main()
{
    n = read(); k = read();
    for (int i = 1; i <= n; i++) a[i] = (read() ^ a[i - 1]);
    for (int i = 1; i <= n; i++) {
        for (int j = i - 1, p = 0; j >= 0; j--) {
            if ((a[i] ^ a[j]) > p) p = (a[i] ^ a[j]);
            mx[j][i] = max(mx[j][i - 1], p);
        }
    }
    for (int i = 1; i <= n; i++) {
        s[i][1].l = 0; s[i][1].r = 0;
        s[i][1].w = mx[0][i]; num[i] = 1;
        for (int j = 1; j < i; j++) {
            if (mx[j][i] == mx[j - 1][i]) s[i][num[i]].r++;
            else {
                s[i][++num[i]].l = j;
                s[i][num[i]].r = j;
                s[i][num[i]].w = mx[j][i];
            }
        }
    }
    for (int j = 1; j <= k; j++) {
        for (int i = 1; i <= n; i++) {
            f[i][j % 2] = 0;
            for (int x = 1; x <= num[i]; x++) {
                f[i][j % 2] = max(f[i][j % 2], f[s[i][x].r][(j % 2) ^ 1] + s[i][x].w);
            }
        }
    }
    cout << f[n][k % 2] << "\n";
    return 0;
}
