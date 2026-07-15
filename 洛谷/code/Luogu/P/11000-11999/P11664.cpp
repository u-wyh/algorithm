#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 5e5 + 5;

// 定义RMQ操作函数
int min_op(int x, int y) {
    return min(x, y);
}

template <class S, S (*op)(S, S)>
struct rmq {
    /*
        init : time O(n log n) memory O(n log n)
        query: O(1)
    */
private:
    vector<vector<S>> st;
    int n, lg;

public:
    rmq() : rmq(0) {}
    rmq(int _n) {
        n = _n;
        lg = __lg(n);
        st.resize(lg + 1, vector<S>(n + 1));
    }
    void init(const vector<S>& a) { // 1-indexed
        for (int i = 1; i <= n; i++) st[0][i] = a[i];
        for (int j = 1; j <= lg; j++)
            for (int i = 1; i + (1 << j) - 1 <= n; i++)
                st[j][i] = op(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    }
    void init(S* a) {
        vector<S> tmp(n + 1);
        for (int i = 1; i <= n; i++) tmp[i] = a[i];
        init(tmp);
    }
    S qry(int l, int r) {
        int k = __lg(r - l + 1);
        return op(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

int n, m, p, u, v, w, a[N], c[N], d[N], l_val[N], q, L, R, x, t[N];

// 更新节点入度的函数
void update_node(int v, int p, int& cnt, int d[]) {
    if (p == 1 && !(d[v]++)) cnt++;
    if (p == -1 && !(--d[v])) cnt--;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> p;
    vector<int> b;
    vector<pair<int, int>> g;

    for (int i = 1; i <= m; i++) {
        cin >> u >> v >> w;
        g.emplace_back(w, v);
        b.push_back(w);
    }

    sort(g.begin(), g.end());
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());

    for (int i = 0; i < m; i++) {
        c[i + 1] = g[i].first;
        a[i + 1] = g[i].second;
    }

    int j = 1, cnt = 0;
    c[0] = -1e9;
    rmq<int, min_op> st(m);

    for (int i = 1; i <= m; i++) {
        update_node(a[i], 1, cnt, d);
        while (cnt == n - 1) {
            update_node(a[j], -1, cnt, d);
            j++;
        }
        l_val[i] = c[j - 1];
        t[i] = c[i] - l_val[i];
    }
    st.init(t);

    cin >> q;
    while (q--) {
        cin >> L >> R >> x;
        int mc = 2e9;
        int pos = upper_bound(c + 1, c + m + 1, R) - c - 1;
        if (pos && l_val[pos] >= L) {
            cout << "Yes\n";
            continue;
        }
        if (pos) mc = L - l_val[pos];
        int sop = lower_bound(l_val + 1, l_val + m + 1, L) - l_val;
        if (pos + 1 != sop) mc = min(mc, st.qry(pos + 1, sop - 1) - R + L);
        if (sop <= m) mc = min(mc, c[sop] - R);
        cout << (mc <= x ? "Yes\n" : "No\n");
    }
    return 0;
}