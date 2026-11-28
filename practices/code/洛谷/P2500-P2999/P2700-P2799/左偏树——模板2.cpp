// https://www.luogu.com.cn/problem/P2713
// 题意：给 n 个士兵的分数，每人起初单独成团。
// M i j 合并 i、j 所在的团；同团或有人已被删则忽略。
// K i 删除 i 所在团内分数最低的人。
// 输出：对每次 K 输出被删者分数，若 i 已被删输出 0。
// 数据范围：1 <= n <= 10^6，1 <= m <= 10^5。
// 分数互不相同，0 <= a_i <= 10^7。
// 难度评分：2000（洛谷分级换算）
// 算法标签：左偏树、并查集

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000001;
int n, m;
int num[MAXN];
int ls[MAXN];
int rs[MAXN];
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
    fa[i] = fa[i] == i ? i : find(fa[i]);
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
    rs[i] = merge(rs[i], j);
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
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    prepare();
    for (int i = 1; i <= n; i++) {
        cin >> num[i];
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
        string op; cin >> op;
        if (op == "M") {
            int x, y; cin >> x >> y;
            if (num[x] != -1 && num[y] != -1) {
                int l = find(x);
                int r = find(y);
                if (l != r) {
                    merge(l, r);
                }
            }
        } else {
            int x; cin >> x;
            if (num[x] == -1) {
                cout << 0 << endl;
            } else {
                int ans = find(x);
                cout << num[ans] << endl;
                pop(ans);
                num[ans] = -1;
            }
        }
    }
    return 0;
}
