#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;
const int MAXS = 1 << 7;
const long long NEG = -(1LL << 60);

int n, k;

int a[MAXN];

// 合并状态 s 后得到的字符
int resultChar[1 << 8];

// 合并状态 s 获得的分数
long long score[1 << 8];

// dp[l][r][s]
// 区间 [l,r] 最终变成状态 s 时的最大得分
long long dp[MAXN][MAXN][MAXS];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    for (int s = 0; s < (1 << k); ++s) {
        cin >> resultChar[s] >> score[s];
    }

    fill(
        &dp[0][0][0],
        &dp[0][0][0] + 1LL * MAXN * MAXN * MAXS,
        NEG
    );

    // 单个字符不需要进行合并
    for (int i = 1; i <= n; ++i) {
        dp[i][i][a[i]] = 0;
    }

    // 按照区间长度递增计算
    for (int length = 2; length <= n; ++length) {
        for (int l = 1; l + length - 1 <= n; ++l) {
            int r = l + length - 1;

            // 当前区间最终剩余的字符数量
            int currentLength = (length - 1) % (k - 1) + 1;

            // 左半部分需要产生的字符数量
            int leftLength;

            if (currentLength == 1) {
                // 最后一次合并前需要凑出 k 个字符
                leftLength = k - 1;
            } else {
                // 普通拼接，左侧提供 currentLength-1 个字符
                leftLength = currentLength - 1;
            }

            // 右半部分必须能够合并成一个字符
            // 所以分割点每次增加 k-1
            for (int mid = l + leftLength;
                 mid <= r;
                 mid += k - 1) {

                for (int leftMask = 0;
                     leftMask < (1 << leftLength);
                     ++leftMask) {

                    long long leftValue = dp[l][mid - 1][leftMask];

                    if (leftValue == NEG) {
                        continue;
                    }

                    for (int bit = 0; bit <= 1; ++bit) {
                        long long rightValue = dp[mid][r][bit];

                        if (rightValue == NEG) {
                            continue;
                        }

                        int mask = (leftMask << 1) | bit;
                        long long value = leftValue + rightValue;

                        if (currentLength == 1) {
                            // mask 正好包含 k 个字符
                            int newChar = resultChar[mask];

                            dp[l][r][newChar] = max(
                                dp[l][r][newChar],
                                value + score[mask]
                            );
                        } else {
                            // 还不足 k 个字符，直接拼接
                            dp[l][r][mask] = max(
                                dp[l][r][mask],
                                value
                            );
                        }
                    }
                }
            }
        }
    }

    int finalLength = (n - 1) % (k - 1) + 1;

    long long answer = 0;

    for (int mask = 0; mask < (1 << finalLength); ++mask) {
        answer = max(answer, dp[1][n][mask]);
    }

    cout << answer << '\n';

    return 0;
}