#include <bits/stdc++.h>
using namespace std;

const int N = 4e4 + 1;
typedef int arr[N];
typedef long long ll;

int n, m, Top, Tot;
arr a, b, c, s, t, Num, S;
ll f[82][41][41];

void dfs(int u, int x, int y) {
    int p = Num[u] = Top ? S[Top--] : ++Tot;
    if (!s[u]) {
        for (int i = 0; i <= x; ++i) {
            for (int j = 0; j <= y; ++j) {
                f[p][i][j] = (ll)c[u] * (a[u] + i) * (b[u] + j);
            }
        }
        return;
    }
    dfs(s[u], x + 1, y);
    dfs(t[u], x, y + 1);
    int ls = Num[s[u]], rs = Num[t[u]];
    for (int i = 0; i <= x; ++i) {
        for (int j = 0; j <= y; ++j) {
            f[p][i][j] = min(f[ls][i + 1][j] + f[rs][i][j], f[ls][i][j] + f[rs][i][j + 1]);
        }
    }
    S[++Top] = ls;
    S[++Top] = rs;
}

int main() {
    cin >> n;
    m = 2 * n - 1;
    int u, v;
    for (int i = 1; i <= n - 1; ++i) {
        cin >> u >> v;
        s[i] = u < 0 ? n - 1 - u : u;
        t[i] = v < 0 ? n - 1 - v : v;
    }
    for (int i = n; i <= m; ++i) {
        cin >> a[i] >> b[i] >> c[i];
    }
    dfs(1, 0, 0);
    cout << f[Num[1]][0][0] << endl;
    return 0;
}
