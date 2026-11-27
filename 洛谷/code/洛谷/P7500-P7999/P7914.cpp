// https://www.luogu.com.cn/problem/P7914
// 题意：给定常数 k 与长为 n、由 `(`, `)`, `*`,
// `?` 组成的字符串 S。
// 合法超级括号序列定义为：
// 1) `()`,
// `(T)`（T 为长度在 [1, k] 内的全 `*` 串）合法；
// 2) 若 A, B 合法，则 `AB`, `ATB`（T 同上）合法；
// 3) 若 A 合法，
// 则 `(A)`, `(TA)`, `(AT)`（T 同上）合法；
// 空串不合法。
// 求将所有 `?` 替换为 `(`, `)`
// 或 `*` 得到合法超级括号序列的方案数，对 10^9 + 7 取模。
// 第一行输入 n, k，第二行输入字符串 S。
// 输出一个非负整数。
// 数据范围：1 <= k <= n <= 500。
// 算法标签：区间动态规划
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;

int n, k;
long long dp[510][510][6];
char s[510];

bool compare(int a, int b) {
    return (s[a] == '(' || s[a] == '?') && (s[b] == ')' || s[b] == '?');
}

int main() {
    cin >> n >> k;
    scanf("%s", s + 1);

    // 初始化 dp 数组
    for (int i = 1; i <= n; i++) {
        dp[i][i - 1][0] = 1;
    }

    // 动态规划
    for (int len = 1; len <= n; len++) {
        for (int l = 1; l <= n - len + 1; l++) {
            int r = l + len - 1;

            // 处理长度为 len 的子串
            if (len <= k) {
                dp[l][r][0] = dp[l][r - 1][0] && (s[r] == '*' || s[r] == '?');
            }

            if (len >= 2) {
                if (compare(l, r)) {
                    dp[l][r][1] = (dp[l + 1][r - 1][0] + dp[l + 1][r - 1][2] + dp[l + 1][r - 1][3] + dp[l + 1][r - 1][4]) % MOD;
                }

                for (int i = l; i < r; i++) {
                    dp[l][r][2] = (dp[l][r][2] + dp[l][i][3] * dp[i + 1][r][0]) % MOD;
                    dp[l][r][3] = (dp[l][r][3] + (dp[l][i][2] + dp[l][i][3]) * dp[i + 1][r][1]) % MOD;
                    dp[l][r][4] = (dp[l][r][4] + (dp[l][i][4] + dp[l][i][5]) * dp[i + 1][r][1]) % MOD;
                    dp[l][r][5] = (dp[l][r][5] + dp[l][i][4] * dp[i + 1][r][0]) % MOD;
                }
            }

            dp[l][r][5] = (dp[l][r][5] + dp[l][r][0]) % MOD;
            dp[l][r][3] = (dp[l][r][3] + dp[l][r][1]) % MOD;
        }
    }

    // 输出结果
    cout << dp[1][n][3] << endl;
    return 0;
}
