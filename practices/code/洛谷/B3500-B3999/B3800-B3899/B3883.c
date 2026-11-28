// https://www.luogu.com.cn/problem/B3883
// 题意：给一个正整数 n，统计从 1 到 n 有多少个顺读倒读相同的整数。
// 答案对 20091119 取模。
// 数据范围：1 ≤ n ≤ 10^100。
// 难度评分：1700（洛谷分级换算）
// 算法标签：数位动态规划、记忆化搜索

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
