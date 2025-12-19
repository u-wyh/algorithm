#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int sg[1001], a[1001];

int SG(int m) {
    if (sg[m] != -1)
        return sg[m];

    int k = 0;
    for (int i = 1; i * i <= m; ++i)
        if (m % i == 0) {
            if (i < m)
                k ^= SG(i);
            if (m / i > 1 && m / i < m && i * i != m)
                k ^= SG(m / i);
        }

    bool flag[1001];
    memset(flag, 0, sizeof(flag));
    for (int i = 1; i * i <= m; ++i)
        if (m % i == 0) {
            if (i < m)
                flag[k ^ sg[i]] = true;
            if (m / i > 1 && m / i < m && i * i != m)
                flag[k ^ sg[m / i]] = true;
        }

    int t = 0;
    while (flag[t])
        t++;
    return sg[m] = t;
}

void work(int n) {
    memset(sg, -1, sizeof(sg));
    sg[1] = 0;
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        ans ^= SG(a[i]);
    }
    if (ans != 0)
        printf("freda\n");
    else
        printf("rainbow\n");
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF)
        work(n);
    return 0;
}
