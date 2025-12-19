#include <stdio.h>
#include <string.h>

int n, m;
long long  diff[1000011], need[1000011], rest[1000011], r[1000011], l[1000011], d[1000011];

int isok(int x) {
    memset(diff, 0, sizeof(diff));
    for (int i = 1; i <= x; i++) {
        diff[l[i]] += d[i];
        if (r[i] + 1 <= n) {
            diff[r[i] + 1] -= d[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        need[i] = need[i - 1] + diff[i];
        if (need[i] > rest[i]) return 0;
    }
    return 1;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &rest[i]);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%lld%lld%lld", &d[i], &l[i], &r[i]);
    }
    int begin = 1, end = m;
    if (isok(m)) {
        printf("0\n");
        return 0;
    }
    while (begin < end) {
        int mid = (begin + end) / 2;
        if (isok(mid)) {
            begin = mid + 1;
        } else {
            end = mid;
        }
    }
    printf("-1\n%d\n", begin);
    return 0;
}
