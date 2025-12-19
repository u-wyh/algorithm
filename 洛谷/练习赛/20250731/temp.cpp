#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cctype>
#include <set>
using namespace std;

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

vector<int> get_factors(int x) {
    vector<int> factors;
    if (x == 0) return factors;
    for (int i = 1; i * i <= x; i++) {
        if (x % i == 0) {
            factors.push_back(i);
            if (i != x / i) {
                factors.push_back(x / i);
            }
        }
    }
    return factors;
}

bool check(int d, const vector<int>& a, int n) {
    if (d == 0) return false;
    long long k = -1;
    int L = n + 1, R = -1;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int r = a[i] % d;
        if (r < 0) r += d;
        r %= d;
        if (r != 0) {
            if (k == -1) {
                k = r;
            } else if (r != k) {
                return false;
            }
            cnt++;
            if (i < L) L = i;
            if (i > R) R = i;
        }
    }
    if (cnt == 0) {
        return true;
    }
    if (R - L + 1 != cnt) {
        return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        if (n == 1) {
            cout << 0 << '\n';
            continue;
        }

        long long g0 = 0;
        for (int i = 1; i < n; i++) {
            long long diff = abs(static_cast<long long>(a[i]) - static_cast<long long>(a[i-1]));
            g0 = gcd(g0, diff);
        }

        if (g0 == 0) {
            cout << 0 << '\n';
            continue;
        }

        long long g_orig = 0;
        for (int i = 0; i < n; i++) {
            g_orig = gcd(g_orig, a[i]);
        }

        long long ans = max(g0, g_orig);

        vector<int> factors1 = get_factors(a[0]);
        vector<int> factors2 = get_factors(a[n-1]);

        long long d_max = 0;

        for (int d : factors1) {
            if (check(d, a, n)) {
                if (static_cast<long long>(d) > d_max) {
                    d_max = d;
                }
            }
        }

        for (int d : factors2) { 
            if (check(d, a, n)) {
                if (static_cast<long long>(d) > d_max) {
                    d_max = d;
                }
            }
        }

        ans = max(ans, d_max);
        cout << ans << '\n';
    }

    return 0;
}