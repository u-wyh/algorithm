#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;
int val[5][5], lin[5], col[5], cr1, cr2;
int numl[5], numc[5], num1, num2;
struct node { int x, y; } sr[20];

void update(int x, int y, int v) {
    lin[x] += v; col[y] += v;
    if (x == y) cr1 += v;
    if (x + y == 5) cr2 += v;
}

void calc(int x, int y, int v) {
    numl[x] += v; numc[y] += v;
    if (x == y) num1 += v;
    if (x + y == 5) num2 += v;
}

// 检查在(x,y)填v是否合法
bool check(int x, int y, int v) {
    if (v <= 0) return false;
    if (lin[x] < v + numl[x] - 1) return false;  // 行剩余空间不够
    if (col[y] < v + numc[y] - 1) return false;  // 列剩余空间不够
    if (x == y     && cr1 < v + num1 - 1) return false;
    if (x + y == 5 && cr2 < v + num2 - 1) return false;
    return true;
}

// (x,y)最大可填值：各约束剩余量 - (其余空格至少填1) + 1
inline int limit(int x, int y) {
    int lim = min(lin[x] - numl[x] + 1, col[y] - numc[y] + 1);
    if (x == y)     lim = min(lim, cr1 - num1 + 1);
    if (x + y == 5) lim = min(lim, cr2 - num2 + 1);
    return lim;
}

inline bool cmp(const node& a, const node& b) {
    return limit(a.x, a.y) < limit(b.x, b.y);
}

int tot; // 未知格子总数

void dfs(int pos) {
    if (pos > tot) {
        // 验证所有约束（保险）
        for (int i = 1; i <= 4; i++) if (lin[i] || col[i]) return;
        if (cr1 || cr2) return;
        for (int i = 1; i <= 4; i++) {
            for (int j = 1; j <= 4; j++)
                cout << val[i][j] << " \n"[j == 4];
        }
        exit(0);
    }

    int x = sr[pos].x, y = sr[pos].y;

    // 唯一确定情况：直接推导，不枚举
    if (numl[x] == 1) {
        if (!check(x, y, lin[x])) return;
        val[x][y] = lin[x];
        update(x, y, -val[x][y]); calc(x, y, -1);
        dfs(pos + 1);
        update(x, y, val[x][y]); calc(x, y, 1); val[x][y] = 0;
        return;
    }
    if (numc[y] == 1) {
        if (!check(x, y, col[y])) return;
        val[x][y] = col[y];
        update(x, y, -val[x][y]); calc(x, y, -1);
        dfs(pos + 1);
        update(x, y, val[x][y]); calc(x, y, 1); val[x][y] = 0;
        return;
    }
    if (x == y && num1 == 1) {
        if (!check(x, y, cr1)) return;
        val[x][y] = cr1;
        update(x, y, -val[x][y]); calc(x, y, -1);
        dfs(pos + 1);
        update(x, y, val[x][y]); calc(x, y, 1); val[x][y] = 0;
        return;
    }
    if (x + y == 5 && num2 == 1) {
        if (!check(x, y, cr2)) return;
        val[x][y] = cr2;
        update(x, y, -val[x][y]); calc(x, y, -1);
        dfs(pos + 1);
        update(x, y, val[x][y]); calc(x, y, 1); val[x][y] = 0;
        return;
    }

    // 枚举：从 lmm/3 开始向大枚举，再回头枚举小值
    int lmm = limit(x, y);
    int mid = max(1, lmm / 3);

    calc(x, y, -1);

    // 先枚举 [mid, lmm]
    update(x, y, -(mid - 1));
    for (int i = mid; i <= lmm; i++) {
        val[x][y] = i;
        update(x, y, -1);
        dfs(pos + 1);
    }
    update(x, y, lmm); // 把update恢复到mid-1次减法后的状态

    // 再枚举 [1, mid-1]
    for (int i = 1; i < mid; i++) {
        val[x][y] = i;
        update(x, y, -1);
        dfs(pos + 1);
    }
    update(x, y, mid - 1);

    calc(x, y, 1);
    val[x][y] = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 1; i <= 4; i++) { cin >> lin[i]; numl[i] = 4; }
    for (int i = 1; i <= 4; i++) { cin >> col[i]; numc[i] = 4; }
    cin >> cr1 >> cr2;
    num1 = num2 = 4;

    for (int t = 0; t < 4; t++) {
        int x, y, v;
        cin >> x >> y >> v;
        x++; y++;
        val[x][y] = v;
        update(x, y, -v);
        calc(x, y, -1);
    }

    tot = 0;
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            if (!val[i][j]) sr[++tot] = {i, j};

    // 按limit从小到大排序（限制最紧的格子先搜）
    sort(sr + 1, sr + tot + 1, cmp);

    dfs(1);
    return 0;
}