#include <stdio.h>
#include <string.h>

int n, m, g[3001], x[3001], y[3001], order[3001], ss[3001], ans[3001], w;

int find(int u) {
    if (g[u] != u) g[u] = find(g[u]);
    return g[u];
}

void merg(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return;
    g[u] = v;
}

int main() {
    memset(ss, 0, sizeof(ss));
    scanf("%d%d", &n, &m);
    for (int j = 1; j <= n; j++) g[j] = j;
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &x[i], &y[i]);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w);
        order[i] = w;
        ss[w] = 1;
    }

    for (int i = n; i > 0; i--) {
        ss[order[i]] = 0;
        for (int j = 1; j <= m; j++)
            if (ss[x[j]] == 0 && ss[y[j]] == 0)
                merg(x[j], y[j]);
        ans[n] = 0; // 注意这里ans[n]的设置可能不是必要的，因为后续会覆盖
        for (int j = 1; j <= n; j++)
            if (find(j) == j && ss[j] == 0)
                ans[i]++;
    }

    for (int i = 1; i <= n - 1; i++) {
        if (ans[i] == 1) printf("YES\n");
        else printf("NO\n");
    }
    printf("YES"); // 注意：这里在循环结束后还打印了一个YES，可能不是预期行为
    return 0;
}
