#include <bits/stdc++.h>
#define X first
#define Y second
using namespace std;
typedef long long int ll;
using pii = pair<int, int>;
const int maxn = 2e5 + 10;
constexpr int mod = 1e9 + 7, S = 1e9 + 10;

struct edge { int to, nxt; } nd[maxn << 1]; 
int h[maxn], cnt = 0, rt[maxn];

inline void add(int u, int v) { 
    nd[cnt].nxt = h[u], nd[cnt].to = v, h[u] = cnt++; 
}

struct Node {
    int l, r, f, g;  // l,r:左右儿子; f:向上链; g:向下链
    Node() { l = r = f = g = 0; }
} t[maxn << 5]; 

int ans = 0, n, a[maxn], tot = 0;

#define ls(x) (t[x].l)
#define rs(x) (t[x].r)
#define f(x) (t[x].f)
#define g(x) (t[x].g)
#define mid (l + r >> 1)

// 插入操作
void ins(int l, int r, int d, int v, int& x, int tp) {
    if (!x) x = ++tot; 
    tp == 1 ? f(x) = max(f(x), v) : g(x) = max(g(x), v); 
    if (l == r) return;
    d <= mid ? ins(l, mid, d, v, ls(x), tp) : ins(mid + 1, r, d, v, rs(x), tp);
}

// 查询操作
Node qry(int l, int r, int ql, int qr, int x) {
    if (ql <= l && r <= qr) return t[x]; 
    Node u, L, R;
    if (ql <= mid) L = qry(l, mid, ql, qr, ls(x)), u.f = L.f, u.g = L.g;
    if (qr > mid) R = qry(mid + 1, r, ql, qr, rs(x)), u.f = max(u.f, R.f), u.g = max(u.g, R.g);
    return u;
}

// 线段树合并
int merge(int x, int y) {
    if (!x || !y) return x | y;
    else {
        // 关键：合并时更新答案
        ans = max({ ans, g(ls(x)) + f(rs(y)), g(ls(y)) + f(rs(x)) });
        f(x) = max(f(x), f(y)), g(x) = max(g(x), g(y));
        ls(x) = merge(ls(x), ls(y)), rs(x) = merge(rs(x), rs(y));
        return x;
    }
}

void dfs(int u, int pa) {
    int st = 0, ed = 0;  // st:向上链长度, ed:向下链长度
    
    for (int i = h[u]; ~i; i = nd[i].nxt) {
        int v = nd[i].to;
        if (v == pa) continue; 
        dfs(v, u);
        
        // 查询子树信息
        int L = qry(0, S, a[u] + 1, S, rt[v]).f;  // 权值>a[u]的向上链
        int R = qry(0, S, 0, a[u] - 1, rt[v]).g;  // 权值<a[u]的向下链
        
        st = max(st, L); ed = max(ed, R);
        
        // 更新包含u的路径答案
        ans = max(ans, qry(0, S, a[u] + 1, S, rt[u]).f + R + 1);
        ans = max(ans, qry(0, S, 0, a[u] - 1, rt[u]).g + L + 1);
        
        rt[u] = merge(rt[u], rt[v]);
    }
    
    // 插入当前节点信息
    ins(0, S, a[u], st + 1, rt[u], 1);  // 向上链
    ins(0, S, a[u], ed + 1, rt[u], 2);  // 向下链
}

int main() {
    memset(h, -1, sizeof(h));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v); add(v, u);
    }
    dfs(1, 0);
    printf("%d\n", ans);
    return 0;
}