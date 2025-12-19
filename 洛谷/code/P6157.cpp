#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

const int N = 100010;

int n, q;
vector<int> g[N];
int w[N];
int fa[N], dep[N], siz[N], son[N];
int top[N], dfn[N], rk[N], index;
map<int, int> cnt;

struct Node {
    int max1, max2;
    Node() : max1(-1), max2(-1) {}
    Node(int a, int b) : max1(a), max2(b) {}
};

Node tr[N << 2];

Node combine(Node a, Node b) {
    if (a.max1 == -1) return b;
    if (b.max1 == -1) return a;
    vector<int> v;
    v.push_back(a.max1);
    if (a.max2 != -1) v.push_back(a.max2);
    v.push_back(b.max1);
    if (b.max2 != -1) v.push_back(b.max2);
    sort(v.begin(), v.end(), greater<int>());
    auto last = unique(v.begin(), v.end());
    v.erase(last, v.end());
    Node res;
    res.max1 = v[0];
    if (v.size() >= 2) res.max2 = v[1];
    else res.max2 = -1;
    return res;
}

void build(int rt, int l, int r) {
    if (l == r) {
        int val = w[rk[l]];
        tr[rt] = Node(val, -1);
        return;
    }
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    tr[rt] = combine(tr[rt << 1], tr[rt << 1 | 1]);
}

void update(int rt, int l, int r, int pos, int val) {
    if (l == r) {
        tr[rt] = Node(val, -1);
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) update(rt << 1, l, mid, pos, val);
    else update(rt << 1 | 1, mid + 1, r, pos, val);
    tr[rt] = combine(tr[rt << 1], tr[rt << 1 | 1]);
}

Node query_seg(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tr[rt];
    int mid = (l + r) >> 1;
    Node res;
    if (L <= mid) res = combine(res, query_seg(rt << 1, l, mid, L, R));
    if (R > mid) res = combine(res, query_seg(rt << 1 | 1, mid + 1, r, L, R));
    return res;
}

void dfs1(int u, int f) {
    fa[u] = f;
    dep[u] = dep[f] + 1;
    siz[u] = 1;
    son[u] = 0;
    for (int v : g[u]) {
        if (v == f) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = ++index;
    rk[index] = u;
    if (son[u]) dfs2(son[u], t);
    for (int v : g[u]) {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

Node query_chain(int x, int y) {
    Node res;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        Node tmp = query_seg(1, 1, n, dfn[top[x]], dfn[x]);
        res = combine(res, tmp);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    Node tmp = query_seg(1, 1, n, dfn[x], dfn[y]);
    res = combine(res, tmp);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        cnt[w[i]]++;
    }

    dep[0] = 0;
    dfs1(1, 0);
    index = 0;
    dfs2(1, 1);
    build(1, 1, n);

    cin >> q;
    while (q--) {
        int opt, x, y;
        cin >> opt >> x >> y;
        if (opt == 0) {
            int old_val = w[x];
            w[x] += y;
            update(1, 1, n, dfn[x], w[x]);
            cnt[old_val]--;
            if (cnt[old_val] == 0) cnt.erase(old_val);
            cnt[w[x]]++;
        } else {
            Node res = query_chain(x, y);
            if (res.max2 == -1) {
                cout << -1 << '\n';
            } else {
                int a = res.max2;
                int b = res.max1;
                cnt[a]--;
                cnt[b]--;
                int M1 = -1, M2 = -1;
                for (auto it = cnt.rbegin(); it != cnt.rend(); it++) {
                    if (it->second > 0) {
                        if (M1 == -1) {
                            M1 = it->first;
                        } else {
                            M2 = it->first;
                            break;
                        }
                    }
                }
                cnt[a]++;
                cnt[b]++;
                cout << a << " " << M2 << '\n';
            }
        }
    }
    return 0;
}