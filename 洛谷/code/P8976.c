#include <stdio.h>

#define int long long

int T, n, p[100005], a, b;

int main() {
    scanf("%lld", &T);
    while (T--) {
        scanf("%lld%lld%lld", &n, &a, &b);
        for (int i = 1; i <= n; i++) p[i] = i;
        int d = a;
        for (int i = 1; i <= n / 2; i++) d -= p[i];

        int cnt = 1;
        while (d > 0 && cnt <= n / 2) {
            if (d - (p[n - cnt + 1] - p[cnt]) <= 0) break;
            d -= (p[n - cnt + 1] - p[cnt]);
            int temp = p[cnt];
            p[cnt] = p[n - cnt + 1];
            p[n - cnt + 1] = temp;
            cnt++;
        }

        int len = n / 2 - cnt + 1;
        if (len * 2 <= d) {
            printf("-1\n");
            continue;
        }

        if (d > len) {
            int temp = p[cnt];
            p[cnt] = p[cnt + d];
            p[cnt + d] = temp;
        }
        if (d <= len && d > 0) {
            int temp = p[n / 2];
            p[n / 2] = p[n / 2 + d];
            p[n / 2 + d] = temp;
        }

        int tmp1 = 0;
        for (int i = n / 2 + 1; i <= n; i++) tmp1 += p[i];
        if (tmp1 >= b) {
            for (int i = 1; i <= n; i++) printf("%lld ", p[i]);
        } else {
            printf("-1");
        }
        printf("\n");
    }
    return 0;
}
