#include <bits/stdc++.h>
using namespace std;

struct Person {
    long long x, y;
    string name;
};

struct Edge {
    int to, rev, cap, cost;
};

string norm(string s) {
    for (char &c : s) c = tolower(c);
    return s;
}

long long cross(const Person &a, const Person &b, const Person &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool onSegment(const Person &a, const Person &b, const Person &c) {
    if (cross(a, b, c) != 0) return false;
    return min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x)
        && min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y);
}

struct MCMF {
    int n;
    vector<vector<Edge>> g;

    MCMF(int n) : n(n), g(n) {}

    void addEdge(int u, int v, int cap, int cost) {
        Edge a{v, (int)g[v].size(), cap, cost};
        Edge b{u, (int)g[u].size(), 0, -cost};
        g[u].push_back(a);
        g[v].push_back(b);
    }

    pair<int, int> maxCostFlow(int s, int t, int need) {
        int flow = 0, cost = 0;

        while (flow < need) {
            vector<int> dist(n, INT_MIN), inq(n), pv(n), pe(n);
            queue<int> q;

            dist[s] = 0;
            q.push(s);
            inq[s] = 1;

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                inq[u] = 0;

                for (int i = 0; i < (int)g[u].size(); i++) {
                    Edge &e = g[u][i];
                    if (e.cap > 0 && dist[u] != INT_MIN && dist[e.to] < dist[u] + e.cost) {
                        dist[e.to] = dist[u] + e.cost;
                        pv[e.to] = u;
                        pe[e.to] = i;
                        if (!inq[e.to]) {
                            inq[e.to] = 1;
                            q.push(e.to);
                        }
                    }
                }
            }

            if (dist[t] == INT_MIN) break;

            int aug = need - flow;
            for (int v = t; v != s; v = pv[v]) {
                aug = min(aug, g[pv[v]][pe[v]].cap);
            }

            for (int v = t; v != s; v = pv[v]) {
                Edge &e = g[pv[v]][pe[v]];
                e.cap -= aug;
                g[v][e.rev].cap += aug;
            }

            flow += aug;
            cost += aug * dist[t];
        }

        return {flow, cost};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long k;
    int n;
    cin >> k >> n;

    vector<Person> people(2 * n);
    unordered_map<string, int> id;

    for (int i = 0; i < 2 * n; i++) {
        cin >> people[i].x >> people[i].y >> people[i].name;
        people[i].name = norm(people[i].name);
        id[people[i].name] = i;
    }

    vector<vector<int>> val(n, vector<int>(n, 1));

    string a, b;
    while (cin >> a) {
        if (a == "End") break;

        int p;
        cin >> b >> p;
        a = norm(a);
        b = norm(b);

        int u = id[a], v = id[b];

        if (u >= n && v < n) swap(u, v);
        if (u < n && v >= n) {
            val[u][v - n] = p;
        }
    }

    int S = 2 * n, T = 2 * n + 1;
    MCMF mf(2 * n + 2);

    for (int i = 0; i < n; i++) mf.addEdge(S, i, 1, 0);
    for (int j = 0; j < n; j++) mf.addEdge(n + j, T, 1, 0);

    long long limit = k * k;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int woman = n + j;

            long long dx = people[i].x - people[woman].x;
            long long dy = people[i].y - people[woman].y;
            if (dx * dx + dy * dy > limit) continue;

            bool blocked = false;
            for (int t = 0; t < 2 * n; t++) {
                if (t == i || t == woman) continue;
                if (onSegment(people[i], people[woman], people[t])) {
                    blocked = true;
                    break;
                }
            }

            if (!blocked) {
                mf.addEdge(i, woman, 1, val[i][j]);
            }
        }
    }

    auto [flow, ans] = mf.maxCostFlow(S, T, n);
    cout << ans << '\n';

    return 0;
}