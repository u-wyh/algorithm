#include <stdio.h>
#include <stdlib.h>

#define int long long
#define MAX_SIZE 100010

int a[MAX_SIZE];
int b[MAX_SIZE];
int c[MAX_SIZE];
int d[MAX_SIZE];
const int mod = 1e9 + 7;

int main() {
    int n; // 实际上n在后续代码中未使用，可能是题目描述中的一部分
    scanf("%lld", &n);
    int ma;
    scanf("%lld", &ma);
    for (int i = ma; i > 0; i--) {
        scanf("%lld", &a[i]);
    }
    int mb;
    scanf("%lld", &mb);
    for (int i = mb; i > 0; i--) {
        scanf("%lld", &b[i]);
    }

    for (int i = (ma > mb ? ma : mb); i > 0; i--) {
        c[i] = (a[i] > b[i] ? a[i] : b[i]) + 1;
    }
    for (int i = (ma > mb ? ma : mb); i > 0; i--) {
        c[i] = (c[i] > 2 ? c[i] : 2);
    }

    d[1] = 1;
    for (int i = 2; i <= (ma > mb ? ma : mb); i++) {
        d[i] = (d[i - 1] * c[i - 1]) % mod;
    }

    long long ka = 0, kb = 0;
    for (int i = ma; i > 0; i--) {
        ka = (ka + a[i] * d[i]) % mod;
    }
    for (int i = mb; i > 0; i--) {
        kb = (kb + b[i] * d[i]) % mod;
    }

    printf("%lld\n", (ka - kb + mod) % mod); // 特别注意：模意义下的减法
    return 0;
}
