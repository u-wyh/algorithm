// 用途：合并小根堆并删除所在堆最小值。
// 时间：合并与弹出 O(log n)，查堆头均摊近 O(1)。
// 空间：O(n)。
// 注意：初值须非负，-1 用作已删除标记。
// 例题：https://www.luogu.com.cn/problem/P3377
// 题意：合并两堆，并删除某元素所在堆的最小值。
// 思路：左偏堆按根值递归合并，父指针定位元素所属堆。
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

int n, m;

int num[MAXN];
int ls[MAXN];
int rs[MAXN];

// dist 是到最近空右子树的距离，控制合并深度。
int dist[MAXN];

int fa[MAXN];

void prepare() {
    dist[0] = -1;
    for(int i = 1; i <= n; i++) {
        ls[i] = rs[i] = dist[i] = 0;
        fa[i] = i;
    }
}

int find(int i) {
    fa[i] = fa[i] == i ? i : find(fa[i]);//扁平化处理
    return fa[i];
}

int merge(int i, int j) {
    if (i == 0 || j == 0) {
        return i + j;
    }
    if (num[i] > num[j] || (num[i] == num[j] && i > j)) {
        int tmp = i;
        i = j;
        j = tmp;
    }
    rs[i] = merge(rs[i], j);//将右儿子和它做合并
    if (dist[ls[i]] < dist[rs[i]]) {
        int tmp = ls[i];
        ls[i] = rs[i];
        rs[i] = tmp;
    }
    dist[i] = dist[rs[i]] + 1;
    fa[ls[i]] = fa[rs[i]] = i;
    return i;
}

int pop(int i) {
    fa[ls[i]] = ls[i];
    fa[rs[i]] = rs[i];
    fa[i] = merge(ls[i], rs[i]);
    ls[i] = rs[i] = dist[i] = 0;
    return fa[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    prepare();
    for (int i = 1; i <= n; i++) {
        cin >> num[i];
    }
    for (int i = 1; i <= m; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y;
            cin >> x >> y;
            if (num[x] != -1 && num[y] != -1) {
                int l = find(x);
                int r = find(y);
                if (l != r) {
                    merge(l, r);
                }
            }
        } else {
            int x;
            cin >> x;
            if (num[x] == -1) {
                cout << -1 << "\n";
            } else {
                int ans = find(x);
                cout << num[ans] << "\n";
                pop(ans);
                num[ans] = -1;
            }
        }
    }
    return 0;
}
