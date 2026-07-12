#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2000000 + 5;
const int MAXA = 2000000 + 5;
const int BASE = 1 << 21; // 2097152，大于 2e6
const int INF = 1e9;

class FastIO {
public:
    static const int S = 1 << 20;

    char ibuf[S], obuf[S];
    int ipos, ilen, opos;

    FastIO() {
        ipos = ilen = opos = 0;
    }

    ~FastIO() {
        flush();
    }

    char gc() {
        if (ipos == ilen) {
            ilen = fread(ibuf, 1, S, stdin);
            ipos = 0;
            if (ilen == 0) return EOF;
        }
        return ibuf[ipos++];
    }

    int read() {
        int x = 0;
        char c = gc();

        while (c < '0' || c > '9') c = gc();

        while (c >= '0' && c <= '9') {
            x = x * 10 + c - '0';
            c = gc();
        }

        return x;
    }

    void pc(char c) {
        if (opos == S) flush();
        obuf[opos++] = c;
    }

    void write(int x) {
        if (x == 0) {
            pc('0');
            pc('\n');
            return;
        }

        char s[20];
        int cnt = 0;

        while (x) {
            s[++cnt] = char(x % 10 + '0');
            x /= 10;
        }

        while (cnt) pc(s[cnt--]);
        pc('\n');
    }

    void flush() {
        if (opos) {
            fwrite(obuf, 1, opos, stdout);
            opos = 0;
        }
    }
};

FastIO io;

int n, m;

int a[MAXN];
int pre[MAXN], nxt[MAXN];
int lastpos[MAXA];

int L[MAXN], R[MAXN], ans[MAXN];

int head[MAXN];
int qhead[MAXN];
int linkPos[MAXN];
int linkQ[MAXN];

int tree[BASE << 1];

void clear_list() {
    for (int i = 0; i <= n + 1; i++) {
        head[i] = 0;
        qhead[i] = 0;
    }
}

void init_max_tree() {
    for (int i = 1; i < (BASE << 1); i++) {
        tree[i] = 0;
    }
}

void init_min_tree() {
    for (int i = 1; i < (BASE << 1); i++) {
        tree[i] = INF;
    }
}

void update_max(int pos, int val) {
    int p = BASE + pos - 1;

    if (tree[p] >= val) return;

    tree[p] = val;
    p >>= 1;

    while (p) {
        int v = max(tree[p << 1], tree[p << 1 | 1]);

        if (tree[p] == v) break;

        tree[p] = v;
        p >>= 1;
    }
}

void update_min(int pos, int val) {
    int p = BASE + pos - 1;

    if (tree[p] <= val) return;

    tree[p] = val;
    p >>= 1;

    while (p) {
        int v = min(tree[p << 1], tree[p << 1 | 1]);

        if (tree[p] == v) break;

        tree[p] = v;
        p >>= 1;
    }
}

int query_max(int l, int r) {
    int res = 0;

    l = BASE + l - 1;
    r = BASE + r - 1;

    while (l <= r) {
        if (l & 1) res = max(res, tree[l++]);
        if (!(r & 1)) res = max(res, tree[r--]);

        l >>= 1;
        r >>= 1;
    }

    return res;
}

int query_min(int l, int r) {
    int res = INF;

    l = BASE + l - 1;
    r = BASE + r - 1;

    while (l <= r) {
        if (l & 1) res = min(res, tree[l++]);
        if (!(r & 1)) res = min(res, tree[r--]);

        l >>= 1;
        r >>= 1;
    }

    return res;
}

int main() {
    n = io.read();
    m = io.read();

    for (int i = 1; i <= n; i++) {
        a[i] = io.read();

        // pre[i] 表示 a[i] 上一次出现的位置
        pre[i] = lastpos[a[i]];
        lastpos[a[i]] = i;
    }

    for (int i = 1; i <= n; i++) {
        lastpos[a[i]] = 0;
    }

    for (int i = n; i >= 1; i--) {
        // nxt[i] 表示 a[i] 下一次出现的位置
        if (lastpos[a[i]] == 0) {
            nxt[i] = n + 1;
        } else {
            nxt[i] = lastpos[a[i]];
        }

        lastpos[a[i]] = i;
    }

    for (int i = 1; i <= m; i++) {
        L[i] = io.read();
        R[i] = io.read();
        ans[i] = 0;
    }

    // 第一类：
    // pre[pos] < l
    // pos 是 a[pos] 在 [l,r] 中第一次出现
    // 可以取 [l,pos-1]，长度 pos-l
    clear_list();

    for (int pos = 1; pos <= n; pos++) {
        linkPos[pos] = head[pre[pos]];
        head[pre[pos]] = pos;
    }

    for (int id = 1; id <= m; id++) {
        linkQ[id] = qhead[L[id]];
        qhead[L[id]] = id;
    }

    init_max_tree();

    for (int l = 1; l <= n; l++) {
        for (int pos = head[l - 1]; pos; pos = linkPos[pos]) {
            update_max(pos, pos);
        }

        for (int id = qhead[l]; id; id = linkQ[id]) {
            int mx = query_max(L[id], R[id]);

            if (mx != 0) {
                ans[id] = max(ans[id], mx - L[id]);
            }
        }
    }

    // 第二类：
    // nxt[pos] <= r
    // pos 和 nxt[pos] 是同一个值的相邻两次出现
    // 可以取 [pos+1,nxt[pos]-1]
    clear_list();

    for (int pos = 1; pos <= n; pos++) {
        if (nxt[pos] <= n) {
            linkPos[pos] = head[nxt[pos]];
            head[nxt[pos]] = pos;
        }
    }

    for (int id = 1; id <= m; id++) {
        linkQ[id] = qhead[R[id]];
        qhead[R[id]] = id;
    }

    init_max_tree();

    for (int r = 1; r <= n; r++) {
        for (int pos = head[r]; pos; pos = linkPos[pos]) {
            update_max(pos, nxt[pos] - pos - 1);
        }

        for (int id = qhead[r]; id; id = linkQ[id]) {
            int mx = query_max(L[id], R[id]);
            ans[id] = max(ans[id], mx);
        }
    }

    // 第三类：
    // nxt[pos] > r
    // pos 是 a[pos] 在 [l,r] 中最后一次出现
    // 可以取 [pos+1,r]，长度 r-pos
    clear_list();

    for (int pos = 1; pos <= n; pos++) {
        linkPos[pos] = head[nxt[pos]];
        head[nxt[pos]] = pos;
    }

    for (int id = 1; id <= m; id++) {
        linkQ[id] = qhead[R[id]];
        qhead[R[id]] = id;
    }

    init_min_tree();

    for (int r = n; r >= 1; r--) {
        for (int pos = head[r + 1]; pos; pos = linkPos[pos]) {
            update_min(pos, pos);
        }

        for (int id = qhead[r]; id; id = linkQ[id]) {
            int mn = query_min(L[id], R[id]);

            if (mn != INF) {
                ans[id] = max(ans[id], R[id] - mn);
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        io.write(ans[i]);
    }

    return 0;
}