// 用途：时间分块统计某位置过去各时刻达到阈值的次数。
// 时间：总计 O(n+q√q log q)，q 为操作数。
// 空间：O(n+q)。
// 例题：https://www.luogu.com.cn/problem/P3863
// 题意：区间加可为负数；询问某位置在当前操作之前有多少个时刻的值不小于阈值。
// 思路：按位置扫描，把区间加拆成两个位置事件；用时间轴分块支持后缀加与历史时刻阈值计数。
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXB = 501;

int n, m;
int arr[MAXN];

// op == 1 表示修改事件、位置x、时刻t、修改效果v、空缺
// op == 2 表示查询事件、位置x、时刻t、查询标准v、问题编号q
struct Event {
    int op, x, t, v, q;
};

bool EventCmp(Event &a, Event &b) {
    return a.x != b.x ? a.x < b.x : a.t < b.t;
}

Event event[MAXN << 2];
int cnte, cntq;

// tim[i] = v，表示在i号时间点，所有数字都增加v
long long tim[MAXN];
// 时间块内的所有值要排序，方便查询 >= v的数字个数
long long sortv[MAXN];

// 时间分块
int blen, bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];
long long lazy[MAXB];

// 每个查询的答案
int ans[MAXN];

void innerAdd(int l, int r, long long v) {
    // 仅边角块逐点修改，并重建这一块的有序副本。
    for (int i = l; i <= r; i++) {
        tim[i] += v;
    }
    for (int i = bl[bi[l]]; i <= br[bi[l]]; i++) {
        sortv[i] = tim[i];
    }
    sort(sortv + bl[bi[l]], sortv + br[bi[l]] + 1);
}

void add(int l, int r, long long v) {
    // 时间轴上的 [l,r] 整段加：边角重建，完整块只加 lazy。
    if (l > r) {
        return;
    }
    if (bi[l] == bi[r]) {
        innerAdd(l, r, v);
    } else {
        innerAdd(l, br[bi[l]], v);
        innerAdd(bl[bi[r]], r, v);
        for (int i = bi[l] + 1; i <= bi[r] - 1; i++) {
            lazy[i] += v;
        }
    }
}

//查询从l到r区间上大于v的数字的个数
int innerQuery(int l, int r, long long v) {
    v -= lazy[bi[l]];
    int ans = 0;
    for (int i = l; i <= r; i++) {
        if (tim[i] >= v) {
            ans++;
        }
    }
    return ans;
}

//查询i号块中大于等于v的数字的个数
int getCnt(int i, long long v) {
    v -= lazy[i];
    int l = bl[i], r = br[i], m, pos = br[i] + 1;
    while (l <= r) {
        m = (l + r) >> 1;
        if (sortv[m] >= v) {
            pos = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return br[i] - pos + 1;
}

int query(int l, int r, long long v) {
    if (l > r) {
        return 0;
    }
    int ans = 0;
    if (bi[l] == bi[r]) {
        ans = innerQuery(l, r, v);
    } else {
        ans += innerQuery(l, br[bi[l]], v);
        ans += innerQuery(bl[bi[r]], r, v);
        for (int i = bi[l] + 1; i <= bi[r] - 1; i++) {
            ans += getCnt(i, v);
        }
    }
    return ans;
}

void addChange(int x, int t, int v) {
    // 位置扫描到 x 时，时刻 t 及以后都应受这次增量影响。
    event[++cnte].op = 1;
    event[cnte].x = x;
    event[cnte].t = t;
    event[cnte].v = v;
}

void addQuery(int x, int t, int v) {
    event[++cnte].op = 2;
    event[cnte].x = x;
    event[cnte].t = t;
    event[cnte].v = v;
    event[cnte].q = ++cntq;
}

void prepare() {
    blen = (int)sqrt(m);
    bnum = (m + blen - 1) / blen;
    for (int i = 1; i <= m; i++) {
        bi[i] = (i - 1) / blen + 1;
    }
    for (int i = 1; i <= bnum; i++) {
        bl[i] = (i - 1) * blen + 1;
        br[i] = min(i * blen, m);
    }
    // 同位置的事件按时刻排，查询只读 [1,t-1]，不会计入当前秒。
    sort(event + 1, event + cnte + 1, EventCmp);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    m++;// 时间轴重新定义，1是初始时刻、2、3 ... m+1
    for (int t = 2, op, l, r, v, x; t <= m; t++) {
        cin >> op;
        if (op == 1) {
            cin >> l >> r >> v;
            // 区间加拆成位置差分：走到 l 生效，越过 r 抵消。
            addChange(l, t, v);
            addChange(r + 1, t, -v);
        } else {
            cin >> x >> v;
            addQuery(x, t, v);
        }
    }
    prepare();
    for (int i = 1; i <= cnte; i++) {
        if (event[i].op == 1) {
            add(event[i].t, m, event[i].v);
        } else {
            ans[event[i].q] = query(1, event[i].t - 1, 1LL * event[i].v - arr[event[i].x]);
        }
    }
    for (int i = 1; i <= cntq; i++) {
        cout << ans[i] << '\n';
    }
    return 0;
}
