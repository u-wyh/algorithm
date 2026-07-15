#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define maxn 100010

typedef uint64_t ull;

ull sd = 111111111111111111ull, sd2, k = 1;
ull qu, n;
ull ans = 0;

ull get_q(int i) {
    sd = (sd2 ^ (sd2 >> 3)) + 998244353;
    return ((sd2 = sd ^ (sd << 37)) & k) + ((i & 1) ? 0 : (n - k - 1));
}

struct FastMod {
    ull b, m;
    FastMod(ull b) : b(b), m(uint64_t((1ULL << 56) / b)) {}
    ull reduce(ull a) {
        ull q = (m * a) >> 56;
        ull r = a - q * b;
        return r >= b ? r - b : r;
    }
};

FastMod F(2);

ull log2(ull x) {
    return 63 - __builtin_clzll(x);  // 注意：__builtin_clzll 是 GCC 的内建函数，可能需要在其他编译器中替换
}

ull getzero(ull x) {
    ull ans = 0;
    while ((x & 1) == 0) {
        x >>= 1;
        ans++;
    }
    return ans;
}

ull getone(ull x) {
    ull ans = 0;
    while (x) {
        if (x % 2) ans++;
        else ans = 0;
        x >>= 1;
    }
    return ans;
}

void init() {
    ull t = getzero(n);
    ull s = getone(n);
    ull logn = log2(n);
    ull len = n >> t;
    F = (FastMod){len};
}

ull get_ans(ull x) {
    if (n == 1) return logn;
    x = F.reduce(x);
    if (x > len >> 1) x = len - x - 1;
    return (x < ((ull)1 << s) - 2 && x & 1) ? logn + 1 : logn;
}

int main() {
    scanf("%" PRIu64, &n);
    sd2 = n;
    while ((k << 1) <= n + 1) k <<= 1;
    k -= 1;
    ull q, q2;
    scanf("%" PRIu64 " %" PRIu64, &q, &q2);
    init();

    for (int i = 1; i <= q; i++) {
        scanf("%" PRIu64, &qu);
        ans += get_ans(qu) * i;
    }

    for (int i = 1; i <= q2; i++) {
        qu = get_q(i);
        ans += get_ans(qu) * (i + q);
    }

    printf("%" PRIu64 "\n", ans);
    return 0;
}
