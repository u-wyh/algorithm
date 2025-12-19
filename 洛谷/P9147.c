#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000005
#define int long long

int n, a[MAX_N], len[MAX_N], ans = 0, cnt = 1, first[MAX_N], last[MAX_N], sec[MAX_N], lastsec[MAX_N];

int main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    first[1] = a[1];

    for (int i = 1; i <= n; i++) {
        if (a[i] > a[i - 1]) {
            len[cnt]++;
            if (len[cnt] == 2) {
                sec[cnt] = a[i];
            }
        } else {
            last[cnt] = a[i - 1];
            if (i > 2 && len[cnt] >= 2) {
                lastsec[cnt] = a[i - 2];
            }
            cnt++;
            len[cnt] = 1;
            first[cnt] = a[i];
        }
        ans = (ans > len[cnt] + 1) ? ans : len[cnt] + 1;
    }

    for (int i = 1; i <= cnt - 1; i++) {
        if (len[i + 1] >= 2 && sec[i + 1] > last[i] + 1) {
            ans = (ans > len[i] + len[i + 1]) ? ans : len[i] + len[i + 1];
        }
        if (len[i] >= 2 && lastsec[i] < first[i + 1] - 1) {
            ans = (ans > len[i] + len[i + 1]) ? ans : len[i] + len[i + 1];
        }
    }

    printf("%lld\n", (ans > n) ? n : ans);
    return 0;
}
