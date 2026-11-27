// https://codeforces.com/problemset/problem/607/B
// 题意：长为 n 的彩色宝石序列，每次可消去一段连续回文子串，剩余部分拼合。
// 输出：消除全部宝石所需的最少操作次数。
// 数据范围：1 <= n <= 500，1 <= c_i <= n。
// 算法标签：区间动态规划
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 505;
const int INF = 505;

int n;
int nums[MAXN];
int dp[MAXN][MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &nums[i]);
    }

    // Initialize DP table
    for (int i = 1; i <= n; i++) {
        dp[i][i] = 1;  // Single character is a palindrome
    }

    for (int len = 2; len <= n; len++) {  // Subsequence length from 2 to n
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            if (nums[i] == nums[j]) {
                if (len == 2) {
                    dp[i][j] = 1;  // Two identical characters
                } else {
                    dp[i][j] = dp[i + 1][j - 1];  // Try merging with the inner part
                }
            } else {
                dp[i][j] = INF;  // Initialize to a large value
            }
            // Check all possible splits to find the minimum
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
        }
    }

    printf("%d\n", dp[1][n]);
    return 0;
}