#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    vector<int> sum;
    vector<int> tag;

    SegTree(vector<int> &v) {
        n = v.size();
        sum.resize(4 * n + 10, 0);
        tag.resize(4 * n + 10, 0);
        if (n > 0) {
            build(1, 1, n, v);
        }
    }

    void build(int p, int l, int r, vector<int>& v) {
        if (l == r) {
            sum[p] = v[l - 1];
            tag[p] = 0;
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, v);
        build(p << 1 | 1, mid + 1, r, v);
        sum[p] = sum[p << 1] + sum[p << 1 | 1];
    }

    void push_down(int p, int l, int r) {
        if (tag[p]) {
            int mid = (l + r) >> 1;
            if (l != r) {
                tag[p << 1] ^= 1;
                sum[p << 1] = (mid - l + 1) - sum[p << 1];
                tag[p << 1 | 1] ^= 1;
                sum[p << 1 | 1] = (r - mid) - sum[p << 1 | 1];
            }
            tag[p] = 0;
        }
    }

    void update(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            sum[p] = (r - l + 1) - sum[p];
            tag[p] ^= 1;
            return;
        }
        push_down(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) {
            update(p << 1, l, mid, ql, qr);
        }
        if (qr > mid) {
            update(p << 1 | 1, mid + 1, r, ql, qr);
        }
        sum[p] = sum[p << 1] + sum[p << 1 | 1];
    }

    int query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return sum[p];
        }
        push_down(p, l, r);
        int mid = (l + r) >> 1;
        int res = 0;
        if (ql <= mid) {
            res += query(p << 1, l, mid, ql, qr);
        }
        if (qr > mid) {
            res += query(p << 1 | 1, mid + 1, r, ql, qr);
        }
        return res;
    }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> init(n + 1);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &init[i]);
    }

    vector<int> groups[6];
    vector<int> pos[6];

    for (int i = 1; i <= n; i++) {
        int r = i % 6;
        groups[r].push_back(init[i]);
        pos[r].push_back(i);
    }

    SegTree* trees[6] = {nullptr};
    for (int i = 0; i < 6; i++) {
        if (!groups[i].empty()) {
            trees[i] = new SegTree(groups[i]);
        } else {
            trees[i] = nullptr;
        }
    }

    while (m--) {
        int op, x, y;
        scanf("%d%d%d", &op, &x, &y);
        vector<int> affected;
        if (op == 1) {
            int base = x % 2;
            if (base == 0) affected = {0, 2, 4};
            else affected = {1, 3, 5};
        } else if (op == 2) {
            int base = x % 3;
            if (base == 0) affected = {0, 3};
            else if (base == 1) affected = {1, 4};
            else affected = {2, 5};
        } else if (op == 3 || op == 4) {
            affected = {0, 1, 2, 3, 4, 5};
        }

        long long ans = 0;
        for (int g : affected) {
            if (trees[g] == nullptr) continue;
            auto& pvec = pos[g];
            int L_idx = lower_bound(pvec.begin(), pvec.end(), x) - pvec.begin();
            int R_idx = upper_bound(pvec.begin(), pvec.end(), y) - pvec.begin() - 1;
            if (L_idx > R_idx) continue;

            if (op == 4) {
                ans += trees[g]->query(1, 1, trees[g]->n, L_idx + 1, R_idx + 1);
            } else {
                trees[g]->update(1, 1, trees[g]->n, L_idx + 1, R_idx + 1);
            }
        }
        if (op == 4) {
            printf("%lld\n", ans);
        }
    }

    for (int i = 0; i < 6; i++) {
        if (trees[i] != nullptr) {
            delete trees[i];
        }
    }

    return 0;
}