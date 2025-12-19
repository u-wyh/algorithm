#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;
const int MAXT = 64000000;
const int INF = 1e9 + 1;

int n, q, m;
int val[MAXN];
int arr[MAXN];

int root[MAXN];

struct Node {
    int ls, rs, sum;
} t[MAXT];
int cnt;
long long ans;

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int find(int val) {
    int l = 1, r = m, ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (arr[mid] >= val) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

inline int lowbit(int x) {
    return x & -x;
}

inline int inquery(int jobl, int jobr, int l, int r, int i) {
    if (i == 0) {
        return 0;
    }
    if (jobl <= l && r <= jobr) {
        return t[i].sum;
    } else {
        int ans = 0;
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            ans += inquery(jobl, jobr, l, mid, t[i].ls);
        }
        if (jobr > mid) {
            ans += inquery(jobl, jobr, mid + 1, r, t[i].rs);
        }
        return ans;
    }
}

inline void inadd(int &i, int jobi, int jobv, int l, int r) {
    if (i == 0) {
        i = ++cnt;
        t[i].ls = t[i].rs = t[i].sum = 0;
    }
    if (l == r) {
        t[i].sum += jobv;
        return;
    }
    int mid = (l + r) >> 1;
    if (jobi <= mid) {
        inadd(t[i].ls, jobi, jobv, l, mid);
    } else {
        inadd(t[i].rs, jobi, jobv, mid + 1, r);
    }
    t[i].sum = t[t[i].ls].sum + t[t[i].rs].sum;
}

void add(int x, int v) {
    for (int i = x; i <= n; i += lowbit(i)) {
        inadd(root[i], val[x], v, 1, m);
    }
}

inline long long query(int l, int r, int jobl, int jobr) {
    if (l > r || jobl > jobr) return 0;
    long long ans = 0;
    for (int i = r; i; i -= lowbit(i)) {
        ans += inquery(jobl, jobr, 1, m, root[i]);
    }
    for (int i = l - 1; i; i -= lowbit(i)) {
        ans -= inquery(jobl, jobr, 1, m, root[i]);
    }
    return ans;
}

void compute(int a, int b) {
    if (val[a] == val[b]) {
        return;
    }
    int L = a + 1, R = b - 1;
    if (L <= R) {
        ans -= query(L, R, 1, val[a] - 1);
        ans += query(L, R, val[a] + 1, m);
        ans -= query(L, R, val[b] + 1, m);
        ans += query(L, R, 1, val[b] - 1);
    }
    if (val[a] < val[b]) {
        ans++;
    } else {
        ans--;
    }
    add(a, -1);
    add(b, -1);
    swap(val[a], val[b]);
    add(a, 1);
    add(b, 1);
}

void prepare() {
    int len = n;
    for (int i = 1; i <= n; i++) {
        arr[i] = val[i];
    }
    arr[++len] = INF;
    arr[++len] = -INF;
    sort(arr + 1, arr + len + 1);
    m = 1;
    for (int i = 2; i <= len; i++) {
        if (arr[i] != arr[i - 1]) {
            arr[++m] = arr[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        val[i] = find(val[i]);
        add(i, 1);
    }
}

int tree[MAXN];

void add_tree(int x) {
    while (x <= m) {
        tree[x] += 1;
        x += lowbit(x);
    }
}

int query_tree(int x) {
    int ans = 0;
    while (x) {
        ans += tree[x];
        x -= lowbit(x);
    }
    return ans;
}

int main() {
    n = read();
    for (int i = 1; i <= n; i++) {
        val[i] = read();
    }
    prepare();
    for (int i = 1; i <= n; i++) {
        ans += (i - 1) - query_tree(val[i]);
        add_tree(val[i]);
    }
    printf("%lld\n", ans);
    q = read();
    for (int i = 1; i <= q; i++) {
        int a, b;
        a = read(), b = read();
        if (a > b) {
            swap(a, b);
        }
        compute(a, b);
        printf("%lld\n", ans);
    }
    return 0;
}