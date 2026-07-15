#include <iostream>
#include <cmath>
#include <set>
#include <algorithm>
using namespace std;

typedef long long LL;

LL gcd_binary(LL a, LL b) {
    if (a == 0) return b;
    if (b == 0) return a;
    LL shift = 0;
    while (((a | b) & 1) == 0) {
        a >>= 1;
        b >>= 1;
        shift++;
    }
    while ((a & 1) == 0) {
        a >>= 1;
    }
    do {
        while ((b & 1) == 0) {
            b >>= 1;
        }
        if (a > b) {
            swap(a, b);
        }
        b = b - a;
    } while (b != 0);
    return a << shift;
}

int main() {
    LL M, N;
    long double R;
    cin >> M >> N;
    cin >> R;

    long double min_diff = 1e30;
    LL count = 0;
    LL ans_num = 0, ans_den = 0;
    const long double eps = 1e-14;

    for (LL a = 1; a <= N; a++) {
        long double x = (long double)a * R;
        LL b1 = (LL)floor(x);
        LL b2 = (LL)ceil(x);

        set<LL> cand;
        if (b1 >= 0 && b1 <= M) {
            cand.insert(b1);
        }
        if (b2 >= 0 && b2 <= M) {
            cand.insert(b2);
        }

        for (LL b : cand) {
            long double diff = fabsl((long double)b - x) / (long double)a;
            LL g = gcd_binary(a, b);
            if (g != 1) {
                continue;
            }

            if (diff < min_diff - eps) {
                min_diff = diff;
                count = 1;
                ans_num = b;
                ans_den = a;
            } else if (fabsl(diff - min_diff) <= eps) {
                count++;
            }
        }
    }

    if (count == 1) {
        cout << ans_num << "/" << ans_den << endl;
    } else {
        cout << "TOO MANY" << endl;
    }

    return 0;
}