#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXB = 105;  // 空间上限: 250 * 1e5 * 8 = 200MB

int n, k, q;
long long ans;
int blen;
int nums[MAXN];
int cnt[MAXN];

long long big[MAXB][MAXN];  // 预计算大数贡献
int bigcnt[MAXB];           // 大数出现次数

vector<int> pos[MAXN];      // 小数位置
int vis[MAXN];              // 大数标记

int rk[MAXN];
int tree[MAXN];

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

inline int lowbit(int x) {
    return x & -x;
}

void add(int x, int v) {
    while (x <= k) {
        tree[x] += v;
        x += lowbit(x);
    }
}

int query(int x) {
    int ans = 0;
    while (x) {
        ans += tree[x];
        x -= lowbit(x);
    }
    return ans;
}

void prepare() {
    // 统计出现次数
    for (int i = 1; i <= n; i++) {
        cnt[nums[i]]++;
    }

    // 大数定义: 出现次数 ≥ 400
    vector<int> candidate;
    for (int i = 1; i <= k; i++) {
        if (cnt[i] >= 200) {  // 阈值 T=400
            candidate.push_back(i);
        }
    }
    // 按出现次数排序
    sort(candidate.begin(), candidate.end(), [&](int x, int y) {
        return cnt[x] > cnt[y];
    });
    blen = candidate.size();
    if (blen > 100) blen = 100;  // 大数数量上限250

    // 标记大数
    for (int i = 0; i < blen; i++) {
        vis[candidate[i]] = i + 1;
    }

    // 预计算大数贡献
    for (int i = 1; i <= n; i++) {
        int val = nums[i];
        for (int j = 1; j <= blen; j++) {
            big[j][val] += bigcnt[j];
        }
        if (vis[val]) {
            bigcnt[vis[val]]++;
        } else {
            pos[val].push_back(i);
        }
    }

    // 初始化排列
    for (int i = 1; i <= k; i++) {
        rk[i] = i;
    }

    // 计算初始逆序对
    for (int i = n; i >= 1; i--) {
        ans += query(nums[i] - 1);
        add(nums[i], 1);
    }
}

int main() {
    n = read(), k = read(), q = read();
    for (int i = 1; i <= n; i++) {
        nums[i] = read();
    }

    prepare();

    while (q--) {
        int p = read();
        int x = rk[p], y = rk[p + 1];
        swap(rk[p], rk[p + 1]);

        if (vis[x]) {
            // 公式: ans += (cnt[x]*cnt[y] - 2*f(x,y))
            ans -= 1LL * cnt[x] * cnt[y] - 2LL * big[vis[x]][y];
        } else if (vis[y]) {
            // 公式: ans += (2*f(y,x) - cnt[x]*cnt[y])
            ans -= 2LL * big[vis[y]][x] - 1LL * cnt[x] * cnt[y];
        } else {
            // 双指针计算 f(x,y)
            int delta = 0;
            int p_val = -1;
            for (int i = 0; i < (int)pos[y].size(); i++) {
                int val = pos[y][i];
                while (p_val + 1 < (int)pos[x].size() && pos[x][p_val + 1] < val) {
                    p_val++;
                }
                delta += p_val + 1;
            }
            // 公式: ans += (cnt[x]*cnt[y] - 2*f(x,y))
            ans -= 1LL * cnt[x] * cnt[y] - 2LL * delta;
        }
        printf("%lld\n", ans);
    }
    return 0;
}