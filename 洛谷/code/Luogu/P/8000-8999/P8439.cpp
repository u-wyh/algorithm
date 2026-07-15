#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;
const int MAXI = MAXN << 1;
const int INF = 1e9;

int n;
long long k;

int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int cntg = 1;

int dfncnt;
int dfn[MAXN];
bool cycle[MAXN];
int from[MAXN];

int cntb;
int belong[MAXN];
int all[MAXN];

int cnta;
int arr[MAXN];
int L[MAXN], R[MAXN];

int core[MAXN];
int sz[MAXN];

bool vis[MAXN];
int sta[MAXN];

int one[MAXI];
int cntone;

struct PairItem {
    int a, b;
};

PairItem bad[MAXN];
int cntbad;

long long preOne[MAXI];
long long preB[MAXN];
long long sufA[MAXN];
long long minLoss[MAXN];

inline void addedge(int u, int v) {
    nxt[cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg++;
}

inline void addone(int x) {
    if (x > 0) {
        one[++cntone] = x;
    }
}

inline void addpair(int a, int b) {
    if (b <= 0) return;

    if (2LL * a >= b) {
        addone(a);
        addone(b - a);
    }
    else {
        bad[++cntbad] = {a, b};
    }
}

void dfs(int u) {
    all[cntb]++;
    belong[u] = cntb;
    dfn[u] = ++dfncnt;

    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];

        if (dfn[v] == 0) {
            from[v] = u;
            dfs(v);
        }
        else if (dfn[u] < dfn[v]) {
            cycle[u] = true;
            arr[++cnta] = u;

            for (int j = v; j != u; j = from[j]) {
                cycle[j] = true;
                arr[++cnta] = j;
            }
        }
    }
}

void dfs2(int u, int fa) {
    sz[u] = 1;

    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];

        if (v != fa && !cycle[v]) {
            dfs2(v, u);
            sz[u] += sz[v];
        }
    }
}

int calc(int s, int ban) {
    if (vis[s]) return 0;

    int top = 0;
    int ans = 0;

    sta[++top] = s;
    vis[s] = true;

    while (top) {
        int u = sta[top--];
        ans++;

        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];

            if (v == ban || vis[v]) continue;

            vis[v] = true;
            sta[++top] = v;
        }
    }

    return ans;
}

int needone(long long need) {
    if (need <= 0) return 0;

    int l = 1, r = cntone, ans = INF;

    while (l <= r) {
        int mid = (l + r) >> 1;

        if (preOne[mid] >= need) {
            ans = mid;
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        int u, v;
        cin >> u >> v;

        addedge(u, v);
        addedge(v, u);
    }

    for (int i = 1; i <= n; i++) {
        if (dfn[i] == 0) {
            cntb++;
            L[cntb] = cnta + 1;
            dfs(i);
            R[cntb] = cnta;
        }
    }

    for (int i = 1; i <= cntb; i++) {
        core[i] = n + 1;
    }

    for (int i = 1; i <= n; i++) {
        core[belong[i]] = min(core[belong[i]], i);
    }

    for (int i = 1; i <= cntb; i++) {
        int u = core[i];

        if (!cycle[u]) {
            for (int e = head[u]; e; e = nxt[e]) {
                int v = to[e];
                addone(calc(v, u));
            }
        }
        else {
            int a = 0;
            int keep = 1;

            for (int j = L[i]; j <= R[i]; j++) {
                int x = arr[j];

                for (int e = head[x]; e; e = nxt[e]) {
                    int v = to[e];

                    if (!cycle[v]) {
                        dfs2(v, x);

                        if (x == u) {
                            keep += sz[v];
                            addone(sz[v]);
                        }
                        else {
                            a = max(a, sz[v]);
                        }
                    }
                }
            }

            int b = all[i] - keep;
            addpair(a, b);
        }
    }

    sort(one + 1, one + cntone + 1, greater<int>());

    for (int i = 1; i <= cntone; i++) {
        preOne[i] = preOne[i - 1] + one[i];
    }

    sort(bad + 1, bad + cntbad + 1, [](const PairItem &x, const PairItem &y) {
        return x.b > y.b;
    });

    for (int i = 1; i <= cntbad; i++) {
        preB[i] = preB[i - 1] + bad[i].b;
        minLoss[i] = min(minLoss[i - 1], 1LL * bad[i].b - bad[i].a);
    }

    for (int i = cntbad; i >= 1; i--) {
        sufA[i] = max(sufA[i + 1], 1LL * bad[i].a);
    }

    int ans = INF;

    auto relax = [&](int cost, long long val) {
        int extra = needone(k - val);

        if (extra < INF) {
            ans = min(ans, cost + extra);
        }
    };

    for (int q = 0; q <= cntbad; q++) {
        long long val = preB[q];
        int cost = q * 2;

        relax(cost, val);

        if (q < cntbad) {
            relax(cost + 1, val + sufA[q + 1]);
        }

        if (q >= 1) {
            relax(cost - 1, val - minLoss[q]);
        }
    }

    cout << ans << '\n';

    return 0;
}