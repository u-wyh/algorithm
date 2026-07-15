#include <stdio.h>
#include <stdlib.h>

#define MAX (100000 + 7)
#define LL long long

int N, k;
int a[MAX];
LL l, r, ans1 = -1, ans2 = -1;

LL work(LL im) {
    int ans = 0;
    LL sum = 0;
    for (int i = 1; i <= N; i++) {
        sum = (sum + a[i] > 0) ? sum + a[i] : 0;
        if (sum >= im) {
            sum = 0;
            ans++;
        }
    }
    return ans;
}

int main() {
    scanf("%d%d", &N, &k);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &a[i]);
    }
    l = 1;
    r = 1e18; // 注意l应设为1

    while (l <= r) {
        LL mid = (l + r) >> 1;
        if (work(mid) <= k) {
            r = mid - 1;
            if (work(mid) == k) ans1 = mid; // 注意符合条件才更新答案
        } else {
            l = mid + 1;
        }
    }

    l = 1;
    r = 1e18; // 注意l应设为1

    while (l <= r) {
        LL mid = (l + r) >> 1;
        if (work(mid) >= k) {
            l = mid + 1;
            if (work(mid) == k) ans2 = mid; // 注意符合条件才更新答案
        } else {
            r = mid - 1;
        }
    }

    if (ans1 == -1) {
        puts("-1");
    } else {
        printf("%lld %lld\n", ans1, ans2);
    }

    return 0;
}
