// https://www.luogu.com.cn/problem/P3183
// 题意：输入物种数 n、有向边数 m，
// 以及 m 条能量流动有向边 (a_i, b_i)。
// 在该有向无环食物网中，
// 一条食物链指从入度为 0 的生产者到出度为 0 的顶级消费者的有向路径，
// 单独一个孤立节点不算食物链。
// 输出食物网中不同食物链的总条数。
// 数据范围：1 <= n <= 100000，0 <= m <= 200000，
// 答案在 int 范围内。
// 难度评分：1300（洛谷分级换算）
// 算法标签：记忆化搜索
#include <stdio.h>

struct node {
    int u, w, next;
};

struct node e[200010];
int st[100010], out[100010], ind[100010], f[100010], n, m, a, b, ans, tot, s, end;

void add(int x, int y) {
    e[++tot].u = x;
    e[tot].w = y;
    e[tot].next = st[x];
    st[x] = tot;
}

int dfs(int x) {
    if (f[x]) return f[x];  // 记忆化
    int ans = 0;
    if (out[x] == 0) return 1;
    for (int i = st[x]; i; i = e[i].next) {
        ans += dfs(e[i].w);
    }
    f[x] = ans;  // 记忆化
    return ans;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &a, &b);
        add(a, b);
        out[a]++;
        ind[b]++;
    }
    for (int i = 1; i <= n; i++) {
        if (ind[i] == 0 && out[i] != 0) {  // 注意单独点的情况
            ans += dfs(i);
        }
    }
    printf("%d", ans);
    return 0;
}
