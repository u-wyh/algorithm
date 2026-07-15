// P2629_2.cpp
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU() {}
    DSU(int n) { init(n); }
    void init(int n) {
        p.resize(n + 1);
        r.assign(n + 1, 0);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};

struct OldEdge {
    int u, v, w;
    bool operator<(const OldEdge &o) const { return w < o.w; }
};

struct NewEdge {
    int u, v;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    vector<OldEdge> oldEdges(M);
    for (int i = 0; i < M; i++) {
        cin >> oldEdges[i].u >> oldEdges[i].v >> oldEdges[i].w;
    }
    sort(oldEdges.begin(), oldEdges.end());

    vector<NewEdge> newEdges(K);
    for (int i = 0; i < K; i++) {
        cin >> newEdges[i].u >> newEdges[i].v;
    }

    vector<long long> p(N + 1);
    for (int i = 1; i <= N; i++) cin >> p[i];

    // Step 1: shrink into <= K+1 components
    DSU dsuA(N), dsuB(N);
    for (int i = 0; i < K; i++) dsuA.unite(newEdges[i].u, newEdges[i].v);

    for (auto &e : oldEdges) {
        if (dsuA.find(e.u) != dsuA.find(e.v)) {
            dsuA.unite(e.u, e.v);
            dsuB.unite(e.u, e.v);
        }
    }

    // Map dsuB components to 0..C-1
    unordered_map<int, int> id;
    id.reserve((size_t)N * 2);
    vector<int> compOf(N + 1, -1);
    int C = 0;
    for (int i = 1; i <= N; i++) {
        int r = dsuB.find(i);
        auto it = id.find(r);
        if (it == id.end()) {
            id[r] = C;
            compOf[i] = C++;
        } else {
            compOf[i] = it->second;
        }
    }

    vector<long long> compPop(C, 0);
    for (int i = 1; i <= N; i++) compPop[compOf[i]] += p[i];
    int rootComp = compOf[1];

    // Compress edges
    for (int i = 0; i < K; i++) {
        newEdges[i].u = compOf[newEdges[i].u];
        newEdges[i].v = compOf[newEdges[i].v];
    }

    vector<OldEdge> compOld;
    compOld.reserve(M);
    for (auto &e : oldEdges) {
        int u = compOf[e.u], v = compOf[e.v];
        if (u != v) compOld.push_back({u, v, e.w});
    }

    // Step 2: keep only useful old edges q (MST edges on compressed graph)
    DSU dsuC(C);
    vector<OldEdge> q;
    q.reserve(max(0, C - 1));
    for (auto &e : compOld) {
        if (dsuC.unite(e.u, e.v)) q.push_back(e);
    }

    // Enumerate subsets of new edges
    long long ans = 0;
    const int INF = 0x3f3f3f3f;

    int totalMasks = 1 << K;
    vector<int> parent(C), depth(C);
    vector<long long> sub(C), mn(C);
    vector<vector<pair<int, int>>> g(C);

    for (int mask = 0; mask < totalMasks; mask++) {
        // Build spanning tree over compressed components
        DSU d(C - 1); // dummy; we'll re-init properly below
        d.init(C);
        for (int i = 0; i < C; i++) g[i].clear();

        bool bad = false;
        int used = 0;

        // Add selected new edges first
        for (int i = 0; i < K; i++) {
            if ((mask >> i) & 1) {
                int u = newEdges[i].u, v = newEdges[i].v;
                if (!d.unite(u + 1, v + 1)) { // cycle among selected new edges
                    bad = true;
                    break;
                }
                g[u].push_back({v, -1}); // -1 means new edge
                g[v].push_back({u, -1});
                used++;
            }
        }
        if (bad) continue;

        // Add old q edges by Kruskal order
        for (auto &e : q) {
            int u = e.u, v = e.v;
            if (d.unite(u + 1, v + 1)) {
                g[u].push_back({v, e.w});
                g[v].push_back({u, e.w});
                used++;
            }
        }

        if (used != C - 1) continue; // should not happen, but safe

        // DFS from rootComp: parent/depth/subtree sum
        for (int i = 0; i < C; i++) {
            parent[i] = -1;
            depth[i] = 0;
            sub[i] = 0;
            mn[i] = INF;
        }

        vector<int> order;
        order.reserve(C);
        {
            stack<int> st;
            st.push(rootComp);
            parent[rootComp] = rootComp;
            depth[rootComp] = 0;
            while (!st.empty()) {
                int u = st.top();
                st.pop();
                order.push_back(u);
                for (auto &nx : g[u]) {
                    int v = nx.first;
                    if (parent[v] != -1) continue;
                    parent[v] = u;
                    depth[v] = depth[u] + 1;
                    st.push(v);
                }
            }
        }

        for (int i = 0; i < C; i++) sub[i] = compPop[i];
        for (int i = (int)order.size() - 1; i >= 0; i--) {
            int u = order[i];
            if (u != rootComp) sub[parent[u]] += sub[u];
        }

        // For each old q edge, constrain all tree edges on its path by weight w
        for (auto &e : q) {
            int u = e.u, v = e.v, w = e.w;
            while (depth[u] > depth[v]) {
                mn[u] = min(mn[u], (long long)w);
                u = parent[u];
            }
            while (depth[v] > depth[u]) {
                mn[v] = min(mn[v], (long long)w);
                v = parent[v];
            }
            while (u != v) {
                mn[u] = min(mn[u], (long long)w);
                mn[v] = min(mn[v], (long long)w);
                u = parent[u];
                v = parent[v];
            }
        }

        // Revenue from selected new edges
        long long cur = 0;
        for (int i = 0; i < K; i++) {
            if ((mask >> i) & 1) {
                int u = newEdges[i].u, v = newEdges[i].v;
                int child = (depth[u] > depth[v]) ? u : v;
                cur += mn[child] * sub[child];
            }
        }
        ans = max(ans, cur);
    }

    cout << ans << '\n';
    return 0;
}
