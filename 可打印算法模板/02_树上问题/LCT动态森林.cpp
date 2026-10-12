// 用途：维护动态森林的路径异或和，支持连边、断边和点权修改。
// 时间：单次操作均摊 O(log n)。
// 空间：O(n)。
// 注意：查询保证连通；只切已有的直接边。
// 例题：https://www.luogu.com.cn/problem/P3690
// 题意：动态连边、断边、改单点权并查询树上路径异或和。
// 思路：LCT 通过 access/makeroot 暴露路径，用伸展树维护异或信息。
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

int n, m;
int arr[MAXN];

int fa[MAXN];
int ls[MAXN];
int rs[MAXN];

bool rev[MAXN];

int sta[MAXN];

int xorsum[MAXN];

void up(int x) {
    xorsum[x] = xorsum[ls[x]] ^ xorsum[rs[x]] ^ arr[x];
}

bool isroot(int x) {
    return ls[fa[x]] != x && rs[fa[x]] != x;
}

int lr(int x) {
    return ls[fa[x]] == x ? 0 : 1;
}

void reverse(int x) {
    if (x != 0) {
        swap(ls[x], rs[x]);
        rev[x] = !rev[x];
    }
}

void down(int x) {
    if (rev[x]) {
        reverse(ls[x]);
        reverse(rs[x]);
        rev[x] = false;
    }
}

void rotate(int x) {
    int f = fa[x], g = fa[f];
    if (lr(x) == 0) {
        ls[f] = rs[x];
        if (ls[f] != 0) {
            fa[ls[f]] = f;
        }
        rs[x] = f;
    } else {
        rs[f] = ls[x];
        if (rs[f] != 0) {
            fa[rs[f]] = f;
        }
        ls[x] = f;
    }
    if (!isroot(f)) {
        if (lr(f) == 0) {
            ls[g] = x;
        } else {
            rs[g] = x;
        }
    }
    fa[f] = x;
    fa[x] = g;
    up(f);
    up(x);
}

void splay(int x) {
    int siz = 0;
    sta[++siz] = x;
    for (int y = x; !isroot(y); y = fa[y]) {
        sta[++siz] = fa[y];
    }
    while (siz != 0) {
        down(sta[siz--]);
    }
    while (!isroot(x)) {
        int f = fa[x];
        if (!isroot(f)) {
            if (lr(x) == lr(f)) {
                rotate(f);
            } else {
                rotate(x);
            }
        }
        rotate(x);
    }
}

// access 将原树根到 x 的路径改成一条实链。
void access(int x) {
    for (int y = 0; x != 0; y = x, x = fa[x]) {
        splay(x);
        rs[x] = y;
        up(x);
    }
}

void makeroot(int x) {
    access(x);
    splay(x);
    reverse(x);
}

int findroot(int x) {
    access(x);
    splay(x);
    down(x);
    while (ls[x] != 0) {
        x = ls[x];
        down(x);
    }
    splay(x);
    return x;
}

void split(int x, int y) {
    makeroot(x);
    access(y);
    splay(y);
}

void link(int x, int y) {
    makeroot(x);
    if (findroot(y) != x) {
        fa[x] = y;
    }
}

// 只有 x、y 确为直接相连的树边才断开。
void cut(int x, int y) {
    makeroot(x);
    if (findroot(y) == x && fa[y] == x && ls[y] == 0 && rs[x] == y) {
        fa[y] = rs[x] = 0;
        up(x);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        xorsum[i] = arr[i];
    }
    for (int i = 1, op, x, y; i <= m; i++) {
        cin >> op >> x >> y;
        if (op == 0) {
            split(x, y);
            cout << xorsum[y] << "\n";
        } else if (op == 1) {
            link(x, y);
        } else if (op == 2) {
            cut(x, y);
        } else {
            splay(x);
            arr[x] = y;
            up(x);
        }
    }
    return 0;
}
