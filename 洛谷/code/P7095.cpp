#include <cstdio>
#include <queue>
#include <algorithm>

const int maxn = 100005;

int T, n, ma, mb, fusu, zxy;
int a[maxn], b[maxn], c[maxn], d[maxn], tmp[maxn];

inline bool cmp(const int x, const int y) {
    return a[x] < a[y];
}

struct Cmp {
    inline bool operator()(const int x, const int y) {
        return b[x] > b[y];
    }
};

bool check1(long long x) {
    int i = 1;
    while (x >= a[tmp[i]]) {
        x += c[tmp[i]];
        if (++i > n) return true;
    }
    return false;
}

bool check2(long long x) {
    std::priority_queue<int, std::vector<int>, Cmp> Q;
    int i = 1, j;
    long long y = fusu;

    while (true) {
        while (i <= n && a[tmp[i]] <= y) {
            Q.push(tmp[i++]);
        }
        if (Q.empty()) {
            return i > n;
        }
        bool flag = false;
        while (!Q.empty() && b[j = Q.top()] <= x) {
            flag = true;
            Q.pop();
            y += c[j];
            x += d[j];
        }
        if (!flag) return false;
    }
}

int main() {
    scanf("%d%d", &T, &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d%d%d", a + i, b + i, c + i, d + i);
        ma = std::max(ma, a[i]);
        mb = std::max(mb, b[i]);
        tmp[i] = i;
    }

    std::sort(tmp + 1, tmp + 1 + n, cmp);

    // Binary search for fusu
    for (int l = 0, r = ma, mid = (l + r) >> 1; l <= r; mid = (l + r) >> 1) {
        if (check1(mid)) {
            fusu = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    // Binary search for zxy
    for (int l = 0, r = mb, mid = (l + r) >> 1; l <= r; mid = (l + r) >> 1) {
        if (check2(mid)) {
            zxy = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    printf("%d %d\n", fusu, zxy);
    return 0;
}
