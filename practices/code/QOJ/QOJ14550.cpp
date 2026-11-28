// https://qoj.ac/problem/14550
// 题意：输入模式串 S 和小写字母串 T。
// S 由小写字母和通配符 * 构成。
// 每个 * 可替换为任意小写字母串，包含空串。
// 输出：T 中能由 S 生成的非空连续子串个数。
// 按子串的位置计数。
// 数据范围：两串长度均为 1 到 5*10^5，
// S 中最多有 10 个通配符。
// 难度评分：2300（估算）
// 算法标签：字符串哈希、动态规划、贪心
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int BASE = 499;
const int MOD = 1e9+7;
const int MAXN = 5e5+5;
const int MAXM = 15;

int n, m;
int ans = 0;
bool flag;
char s[MAXN];
char t[MAXN];
int p[MAXN];
int h[MAXN];

int cnt;
int val[MAXM];
int len[MAXM];

int pre[MAXN][MAXM];
bool ok[MAXN][MAXM];
int sum[MAXN];

int gethash(int l, int r) {
    return (h[r] - h[l-1] * p[r-l+1] % MOD + MOD) % MOD;
}

void prepare() {
    n = strlen(s+1), m = strlen(t+1);
    p[0] = 1;
    for (int i = 1; i <= m; i++) {
        p[i] = (p[i-1] * BASE) % MOD;
    }
    for (int i = 1; i <= m; i++) {
        h[i] = (h[i-1] * BASE + (t[i] - 'a' + 1)) % MOD;
    }
    if (s[1] != '*') {
        ++cnt;
    } else {
        flag = true;
    }
    for (int i = 1; i <= n; i++) {
        if (s[i] == '*') {
            if (i < n && s[i+1] != '*') {
                ++cnt;
            }
        } else {
            val[cnt] = (val[cnt] * BASE + (s[i] - 'a' + 1)) % MOD;
            len[cnt]++;
        }
    }
}

void compute() {
    pre[0][0] = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= cnt; j++) {
            pre[i][j] = pre[i-1][j];
        }
        for (int j = 1; j <= cnt; j++) {
            if (i >= len[j] && pre[i-len[j]][j-1] && gethash(i-len[j]+1, i) == val[j]) {
                ok[i][j] = true;
                pre[i][j] = i;
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        if (ok[i][1]) {
            if (flag) {
                sum[i] = i - len[1] + 1;
            } else {
                if (pre[i-1][1] > 0) {
                    sum[i] = sum[pre[i-1][1]] + 1;
                } else {
                    sum[i] = 1;
                }
            }
        }
    }
    int all = 0;
    for (int i = 1; i <= cnt; i++) {
        all += len[i];
    }
    int lst = m;
    for (int i = m; i >= all; i--) {
        if (!ok[i][cnt]) {
            continue;
        }
        int now = i;
        for (int j = cnt; j >= 2; j--) {
            now = pre[now - len[j]][j-1];
        }
        int tmp = 1;
        if (s[n] == '*') {
            tmp = lst - i + 1;
            lst = i - 1;
        }
        tmp *= sum[now];
        ans += tmp;
    }
}

signed main() {
    scanf("%s %s", s+1, t+1);
    prepare();
    if (cnt == 0) {
        cout << (m * (m + 1) / 2) << endl;
        return 0;
    }
    if (cnt == 1 && len[1] == n) {
        int ans = 0;
        for (int i = n; i <= m; i++) {
            if (gethash(i - n + 1, i) == val[1]) {
                ans++;
            }
        }
        cout << ans << endl;
        return 0;
    }
    compute();
    cout << ans << endl;
    return 0;
}