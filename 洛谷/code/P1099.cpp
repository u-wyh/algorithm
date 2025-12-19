#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
struct edge {
  int v, w;
  edge(int v = 0, int w = 0) {
    this->v = v;
    this->w = w;
  }
};
const int maxn = 300000 + 5;
vector<edge> e[maxn];
int dep[maxn], f[maxn], c;
int dia[maxn], cnt, pres[maxn], posts[maxn];
bool vis[maxn];
int n, s;
void dfs(int u, int fa) {
  f[u] = fa;
  for (auto ed : e[u]) {
    if (ed.v == fa || vis[ed.v]) continue;
    dep[ed.v] = dep[u] + ed.w;
    if (dep[ed.v] > dep[c]) c = ed.v;
    dfs(ed.v, u);
  }
}
void get_diameter() {
  dfs(1, 0);
  dep[c] = 0;
  dfs(c, 0);
  for (int u = c; u; u = f[u]) {
    dia[++cnt] = u;
    pres[cnt] = dep[u];
  }
  reverse(dia + 1, dia + cnt + 1);
  reverse(pres + 1, pres + cnt + 1);
  for (int i = cnt; i > 0; i--) posts[i] = pres[cnt] - pres[i];
}
namespace sub1 {
void solve() {
  int minecc = 1 << 30;
  for (int i = 1; i <= cnt; i++)
    for (int j = i; j <= cnt; j++) {
      if (pres[j] - pres[i] <= s) {
        memset(vis, 0, sizeof(vis));
        for (int k = i; k <= j; k++) vis[dia[k]] = true;
        int ecc = 0;
        for (int k = i; k <= j; k++) {
          dep[dia[k]] = 0, c = 0;
          dfs(dia[k], 0);
          ecc = max(ecc, dep[c]);
        }
        minecc = min(minecc, ecc);
      }
    }
  cout << minecc << endl;
}
}
int main() {
  ios::sync_with_stdio(false);
  cin >> n >> s;
  for (int i = 1; i < n; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    e[u].emplace_back(v, w);
    e[v].emplace_back(u, w);
  }
  get_diameter();
  sub1::solve();
  return 0;
}
