#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL INF = 1e18;

struct Fenw {
    int n;
    vector<LL> tree;
    Fenw(int size) {
        n = size;
        tree.assign(n+1, INF);
    }
    void update(int pos, LL val) {
        if (pos < 1 || pos > n) return;
        while (pos <= n) {
            if (val < tree[pos]) {
                tree[pos] = val;
            }
            pos += pos & -pos;
        }
    }
    LL query(int pos) {
        if (pos < 1) return INF;
        LL res = INF;
        while (pos) {
            if (tree[pos] < res) {
                res = tree[pos];
            }
            pos -= pos & -pos;
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        LL sum_val;
        cin >> n >> k >> sum_val;
        vector<LL> a(n+1);
        for (int i=1; i<=n; i++) {
            cin >> a[i];
        }

        vector<LL> pre(n+1, 0);
        for (int i=1; i<=n; i++) {
            pre[i] = pre[i-1] + a[i];
        }

        vector<Fenw> fenw;
        vector<LL> base(k+1, INF);
        base[0] = 0;
        for (int j=0; j<=k; j++) {
            fenw.push_back(Fenw(n));
        }

        unordered_map<LL, int> mp;
        mp[0] = 0;
        vector<tuple<int, int, LL>> intervals;

        for (int i=1; i<=n; i++) {
            LL x = pre[i] - sum_val;
            if (mp.find(x) != mp.end()) {
                int l0 = mp[x] + 1;
                int r0 = i;
                LL len0 = r0 - l0 + 1;
                intervals.push_back({l0, r0, len0});
            }
            mp[pre[i]] = i;
        }

        LL ans = INF;

        for (auto &t : intervals) {
            int l = get<0>(t);
            int r = get<1>(t);
            LL len = get<2>(t);
            for (int j=1; j<=k; j++) {
                LL min_val = base[j-1];
                if (l-1 >= 1) {
                    LL t_val = fenw[j-1].query(l-1);
                    min_val = min(min_val, t_val);
                }
                if (min_val >= INF) continue;
                LL candidate = min_val + len;
                fenw[j].update(r, candidate);
                if (j == k) {
                    ans = min(ans, candidate);
                }
            }
        }

        if (ans == INF) {
            cout << -1 << endl;
        } else {
            cout << ans << endl;
        }
    }
    return 0;
}