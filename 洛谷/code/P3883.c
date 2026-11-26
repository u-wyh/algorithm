// https://www.luogu.com.cn/problem/P3883
// 题意：给定 n 个国际象棋定式（每个定式含名称及由 k 个步法字符串组成的序列）以及一个包含 m 个步法字符串的棋局。
// 若棋局中完整且连续地包含某个定式的所有步法，则称棋局包含该定式。按定式在输入中的顺序输出棋局包含的所有定式名称（不保证符合真实国际象棋规则）。
// 数据范围：1 <= n <= 2000，1 <= k <= 100000，sum k <= 200000，定式名称长度不超过 50；
// 题目描述中提到棋局步数 m 可达 2000000。
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 105
#define MOD 20091119

char s[MAXN];
int a[MAXN], len;
int dp[2][MAXN];
int temp[MAXN], total;

int check() {
    for (int i = total, j = (len >> 1) + (len & 1); i && j; i--, j--) {
        if (temp[i] > a[j]) return 0;
        if (temp[i] < a[j]) return 1;
    }
    return 1;
}

int dfs(bool lim, int pos) {
    if (pos == (len >> 1)) {
        if (!lim) return 1;
        return check();
    }
    if (dp[lim][pos] != -1) return dp[lim][pos];
    int res = 0;
    for (int i = 0; i <= 9; i++) {
        if (pos == len && !i) continue;
        if (lim && i > a[pos]) break;
        temp[++total] = i;
        res = (res + dfs(lim && i == a[pos], pos - 1)) % MOD;
        total--;
    }
    dp[lim][pos] = res;
    return res;
}

int solve() {
    for (int i = 1; i <= len; i++) a[i] = s[len - i + 1] - '0';
    int res = 0;
    for (int i = len - 1; i > 0; i--) {
        int res2 = 9;
        for (int j = i - 1; j > (i >> 1); j--) res2 = (res2 * 10) % MOD;
        res = (res + res2) % MOD;
    }
    memset(dp, -1, sizeof(dp));
    res = (res + dfs(true, len)) % MOD;
    return res;
}

int main() {
    scanf("%s", s + 1);
    len = strlen(s + 1);
    printf("%d\n", solve());
    return 0;
}
