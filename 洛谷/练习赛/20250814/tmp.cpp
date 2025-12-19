#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>
#include <bitset>
#include <set>
#include <unordered_set>
#include <queue>
using namespace std;

const int MAXN = 10010;
const int MAX_EDGES = 550000;
const int MAX_SCC = MAXN;
const int W_MAX = 10000;

int n;
int a[MAXN];
vector<int> original_tree_edges;
vector<int> graph[MAXN];
vector<int> rev_graph[MAXN];
int m;
vector<pair<int, int>> extra_edges;

int in_degree_original[MAXN];
int root_original = -1;

int scc_id[MAXN];
int scc_count = 0;
vector<int> scc_nodes[MAX_SCC];
int scc_weight[MAX_SCC];

vector<int> contracted_tree_edges[MAX_SCC];
int in_degree_contracted[MAX_SCC];
int root_contracted = -1;

bitset<W_MAX + 1> dp[MAX_SCC];
int tree_weight[MAX_SCC];

bool visited[MAXN];
stack<int> finish_order;

void dfs1(int u) {
    visited[u] = true;
    for (int v : graph[u]) {
        if (!visited[v]) {
            dfs1(v);
        }
    }
    finish_order.push(u);
}

void dfs2(int u, int comp) {
    visited[u] = true;
    scc_id[u] = comp;
    scc_nodes[comp].push_back(u);
    for (int v : rev_graph[u]) {
        if (!visited[v]) {
            dfs2(v, comp);
        }
    }
}

void kosaraju() {
    memset(visited, false, sizeof(visited));
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs1(i);
        }
    }

    memset(visited, false, sizeof(visited));
    while (!finish_order.empty()) {
        int u = finish_order.top();
        finish_order.pop();
        if (!visited[u]) {
            dfs2(u, scc_count);
            scc_count++;
        }
    }
}

void build_contracted_tree() {
    set<pair<int, int>> added_edges;
    for (int u = 1; u <= n; u++) {
        for (int v : graph[u]) {
            if (scc_id[u] != scc_id[v]) {
                int scc_u = scc_id[u];
                int scc_v = scc_id[v];
                if (added_edges.find({scc_u, scc_v}) == added_edges.end()) {
                    contracted_tree_edges[scc_u].push_back(scc_v);
                    in_degree_contracted[scc_v]++;
                    added_edges.insert({scc_u, scc_v});
                }
            }
        }
    }
}

void compute_tree_weight(int u) {
    tree_weight[u] = scc_weight[u];
    for (int v : contracted_tree_edges[u]) {
        compute_tree_weight(v);
        tree_weight[u] += tree_weight[v];
    }
}

void dfs_dp(int u) {
    dp[u].reset();
    dp[u].set(0);
    for (int v : contracted_tree_edges[u]) {
        dfs_dp(v);
        bitset<W_MAX + 1> new_dp;
        for (int a_val = 0; a_val <= W_MAX; a_val++) {
            if (dp[u].test(a_val)) {
                new_dp |= (dp[v] << a_val);
            }
        }
        new_dp &= bitset<W_MAX + 1>().set(); 
        dp[u] = new_dp;
    }
    if (tree_weight[u] <= W_MAX) {
        dp[u].set(tree_weight[u]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    memset(in_degree_original, 0, sizeof(in_degree_original));
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        rev_graph[v].push_back(u);
        in_degree_original[v]++;
        original_tree_edges.push_back(u);
        original_tree_edges.push_back(v);
    }

    for (int i = 1; i <= n; i++) {
        if (in_degree_original[i] == 0) {
            root_original = i;
            break;
        }
    }

    cin >> m;
    set<pair<int, int>> extra_set;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (u == v) continue;
        if (extra_set.find({u, v}) != extra_set.end()) continue;
        extra_set.insert({u, v});
        graph[u].push_back(v);
        rev_graph[v].push_back(u);
        extra_edges.push_back({u, v});
    }

    kosaraju();

    for (int i = 0; i < scc_count; i++) {
        scc_weight[i] = 0;
        for (int node : scc_nodes[i]) {
            scc_weight[i] += a[node];
        }
    }

    build_contracted_tree();

    for (int i = 0; i < scc_count; i++) {
        if (in_degree_contracted[i] == 0) {
            root_contracted = i;
            break;
        }
    }

    compute_tree_weight(root_contracted);

    dfs_dp(root_contracted);

    cout << dp[root_contracted].count() << endl;

    return 0;
}