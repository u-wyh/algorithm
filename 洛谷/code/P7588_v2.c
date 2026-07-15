#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define Size 100000000

unsigned int B[(Size + 32 + 1) >> 5];

void change(int wz, int turn) {
    int add = wz & 31;
    wz >>= 5;
    if (!turn && (B[wz] >> add & 1) && (B[wz] -= (1 << add)));
    if (turn && !(B[wz] >> add & 1) && (B[wz] += (1 << add)));
}

bool find(int wz) {
    return B[wz >> 5] >> (wz & 31) & 1;
}

bool sushu(int a) {
    if (a == 43 || a == 47 || a == 53 || a == 59 || a == 61 || a == 67 || a == 71) {
        return true;
    }
    if (a == 41 || a == 37 || a == 31 || a == 29 || a == 23 || a == 19 || a == 17 || a == 13 || a == 11 || a == 7 || a == 5 || a == 3 || a == 2) {
        return true;
    }
    return false;
}

int dp[10000010];
int ans[10000010];
int k = 0;

void work() {
    const int n = 100000000;
    change(1, 1);
    for (int i = 2; i <= n; ++i) {
        if (!find(i)) {
            dp[++k] = i;
        }
        for (int j = 1; j <= k && i * dp[j] <= n; ++j) {
            change(dp[j] * i, 1);
            if (!(i % dp[j])) {
                break;
            }
        }
    }
    int k1 = k;
    k = 0;
    for (int i = 1; i <= k1; ++i) {
        int sum = 0, t = dp[i];
        while (t) {
            sum += t % 10;
            t /= 10;
        }
        if (sushu(sum)) {
            ans[++k] = dp[i];
        }
    }
}

int main() {
    work();
    int t, l, r;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &l, &r);
        int count = upper_bound(ans + 1, ans + k + 1, r) - lower_bound(ans + 1, ans + k + 1, l);
        printf("%d\n", count);
    }
    return 0;
}
