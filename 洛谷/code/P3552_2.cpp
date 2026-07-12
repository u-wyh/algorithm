#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ll = long long;

const int MAXK = 1000000 + 5;

// 最多需要存：删除点 k + BFS 访问点 n*k
// n*k <= 5e6，k <= 1e6，所以开 6e6 多一点
const int MAXNODE = 6000000 + 10;

// 哈希桶数量，取一个较大的质数，减少冲突
const int MOD = 3000017;

int n, m;
ull st, en;
ull blocked[MAXK];

// 链式哈希表
struct HashTable {
    ull val[MAXNODE];
    int nxt[MAXNODE];
    int head[MOD];
    int tot;

    void clear() {
        tot = 0;
        memset(head, 0, sizeof(head));
    }

    int get_hash(ull x) {
        // 混合一下，避免低位冲突严重
        x ^= x >> 33;
        x *= 0xff51afd7ed558ccdULL;
        x ^= x >> 33;
        x *= 0xc4ceb9fe1a85ec53ULL;
        x ^= x >> 33;
        return x % MOD;
    }

    bool find(ull x) {
        int h = get_hash(x);
        for (int i = head[h]; i; i = nxt[i]) {
            if (val[i] == x) return true;
        }
        return false;
    }

    void insert(ull x) {
        int h = get_hash(x);
        ++tot;
        val[tot] = x;
        nxt[tot] = head[h];
        head[h] = tot;
    }
} hsh;

// 读入一个 01 串，并转成整数
ull read01() {
    string s;
    cin >> s;

    ull x = 0;
    for (char c : s) {
        x = (x << 1) | (c - '0');
    }

    return x;
}

// bfs(start, target) 返回 true 表示：
// 1. 直接搜到了 target
// 2. 或者搜到超过 n*m 个点，说明 start 在唯一大连通块中
bool bfs(ull start, ull target) {
    if (start == target) return true;

    hsh.clear();

    // 先把删除点放进哈希表
    for (int i = 1; i <= m; i++) {
        hsh.insert(blocked[i]);
    }

    static ull q[MAXNODE];

    int head = 0, tail = 0;
    q[tail++] = start;
    hsh.insert(start);

    ll cnt = 1;
    ll limit = 1LL * n * m;

    while (head < tail) {
        ull u = q[head++];

        for (int i = 0; i < n; i++) {
            ull v = u ^ (1ULL << i);

            if (v == target) {
                return true;
            }

            if (hsh.find(v)) {
                continue;
            }

            hsh.insert(v);
            q[tail++] = v;
            cnt++;

            if (cnt > limit) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    st = read01();
    en = read01();

    for (int i = 1; i <= m; i++) {
        blocked[i] = read01();
    }

    if (bfs(st, en) && bfs(en, st)) {
        cout << "TAK\n";
    } else {
        cout << "NIE\n";
    }

    return 0;
}