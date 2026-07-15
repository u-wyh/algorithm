#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const long long INF = 1e18;
typedef long long int LL;
typedef unsigned long long ULL;

int pr[100005], top = 0, ans[100005], cnt;
bool v[100005];

inline bool is_prime(int x) {
    if (x == 1) return false;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

void dfs(int now, int x, int s) {
    if (now == 1) {
        ans[++cnt] = s;
        return;
    }
    if (is_prime(now - 1) && now > pr[x]) {
        ans[++cnt] = s * (now - 1);
    }
    for (int i = x; pr[i] * pr[i] <= now; i++) {
        int t = pr[i];
        int sum = pr[i] + 1;
        while (sum <= now) {
            if (now % sum == 0) {
                dfs(now / sum, i + 1, s * t);
            }
            t *= pr[i];
            sum += t;
        }
    }
}

int main() {
    memset(v, true, sizeof(v));
    v[1] = false;
    for (int i = 2; i <= 100000; i++) {
        if (v[i]) pr[++top] = i;
        for (int j = 1; j <= top && pr[j] * i <= 100000; j++) {
            v[i * pr[j]] = false;
            if (i % pr[j] == 0) break;
        }
    }

    int x;
    while (scanf("%lld", &x) != EOF) {
        cnt = 0;
        dfs(x, 1, 1);
        sort(ans + 1, ans + cnt + 1);
        printf("%lld\n", cnt);
        for (int i = 1; i <= cnt; i++) {
            printf("%lld ", ans[i]);
        }
        if (cnt) puts("");
    }

    return 0;
}
