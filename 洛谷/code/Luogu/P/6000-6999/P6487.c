#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000000000000000LL
#define MAXM 101

long long f[MAXM];
int size;

void build() {
    f[0] = 1;
    f[1] = 2;
    size = 1;
    while (f[size] <= MAXN) {
        f[size + 1] = f[size] + f[size - 1];
        size++;
    }
}

long long bs(long long n) {
    int l = 0;
    int r = size - 1;
    int m;
    long long ans = -1;
    while (l <= r) {
        m = (l + r) / 2;
        if (f[m] <= n) {
            ans = f[m];
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return ans;
}

long long compute(long long n) {
    long long ans = -1, find;
    while (n != 1 && n != 2) {
        find = bs(n);
        if (n == find) {
            ans = find;
            break;
        } else {
            n -= find;
        }
    }
    if (ans != -1) {
        return ans;
    } else {
        return n;
    }
}

int main() {
    build();
    long long n;
    scanf("%lld", &n) ;
    printf("%lld\n", compute(n));
    return 0;
}
