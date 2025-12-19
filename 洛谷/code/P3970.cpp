#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

const long long MOD = 1e9 + 7;

using namespace std;

struct FenwickTree {
    vector<long long> tree;
    int n;

    FenwickTree(int size) : n(size), tree(size + 1, 0) {}

    void add(int x, long long v) {
        for (int i = x; i <= n; i += i & -i) {
            tree[i] = (tree[i] + v) % MOD;
        }
    }

    long long query(int x) {
        long long ans = 0;
        for (int i = x; i > 0; i -= i & -i) {
            ans = (ans + tree[i]) % MOD;
        }
        return ans;
    }
};

int main() {
    int n;
    cin >> n;
    vector<long long> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        b[i] = a[i];
    }

    sort(b.begin() + 1, b.end());
    b.erase(unique(b.begin() + 1, b.end()), b.end());
    unordered_map<long long, int> ma;
    for (int i = 1; i < b.size(); ++i) {
        ma[b[i]] = i;
    }

    FenwickTree ft(n);
    long long cnt = 0;
    vector<long long> lastans(n + 1, 0);
    vector<bool> f(n + 1, false);

    for (int i = 1; i <= n; ++i) {
        int j = ma[a[i]];
        if (!f[j]) {
            long long mid = ft.query(j - 1);
            cnt = (cnt + mid) % MOD;
            ft.add(j, mid + 1);
            lastans[j] = mid;
            f[j] = true;
        } else {
            long long mid = ft.query(j - 1);
            cnt = (cnt + (mid - lastans[j] + MOD) % MOD) % MOD;
            ft.add(j, (mid - lastans[j] + 2 * MOD) % MOD);
            lastans[j] = mid;
        }
    }

    cout << cnt << endl;
    return 0;
}
