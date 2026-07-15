#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAXN = 305;
const ll INF = 1e18;

int n, k;           // 字符串长度 n，合并参数 k
int a[MAXN];        // 原始 01 串（1-indexed）

// 合并表：长度为 k 的 01 模式（对应二进制 0..2^k-1）→ (新字符, 得分)
int merge_char[1 << 8];
ll merge_score[1 << 8];

// dp[l][r][mask]
// 区间 [l, r] 最终被压缩成 mask（二进制位串）时的最大得分
// mask 的位数 = 该区间的压缩长度 L = ((r-l) % (k-1)) + 1
ll dp[MAXN][MAXN][1 << 8];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    for (int s = 0; s < (1 << k); ++s) {
        char ch;
        cin >> ch >> merge_score[s];
        merge_char[s] = ch - '0';
    }

    // 初始化 dp 为 -INF
    fill(&dp[0][0][0], &dp[0][0][0] + 1LL * MAXN * MAXN * (1 << 8), -INF);

    // 基底：单个字符就是它自己，得分 0
    for (int i = 1; i <= n; ++i) dp[i][i][a[i]] = 0;

    // 区间 DP，按长度递增
    for (int len = 2; len <= n; ++len) {
        for (int l = 1, r = l + len - 1; r <= n; ++l, ++r) {
            // 当前区间经过完全压缩后剩余的位数
            int L = (len - 1) % (k - 1) + 1;

            // 对于 len < k 的情况，L = len（无法合并，只能拼接）
            // 对于 len ≡ 1 mod (k-1) 的情况，L = 1（可以合并到 1 位）

            // 构造压缩状态的方式：
            //   将 [l, r] 分成 [l, mid-1] 和 [mid, r]
            //   [mid, r] 必须压缩成 1 位 → 其长度 ≡ 1 (mod k-1)
            //   [l, mid-1] 提供剩余位（L-1 位或 k-1 位）

            int left_bits = (L == 1) ? (k - 1) : (L - 1);

            // mid 起始于 l + left_bits，确保 [l, mid-1] 至少 left_bits 位
            // 步进 k-1 保证 [mid, r] 的长度 ≡ 1 (mod k-1)
            for (int mid = l + left_bits; mid <= r; mid += k - 1) {
                // leftMask 对应 [l, mid-1] 的压缩状态 (left_bits 位)
                for (int left_mask = 0; left_mask < (1 << left_bits); ++left_mask) {
                    ll left_val = dp[l][mid - 1][left_mask];
                    if (left_val == -INF) continue;

                    // bit 对应 [mid, r] 的压缩结果 (1 位)
                    for (int bit = 0; bit <= 1; ++bit) {
                        ll right_val = dp[mid][r][bit];
                        if (right_val == -INF) continue;

                        // 拼接成完整状态：左(left_bits 位) || 右(1 位)
                        int mask = (left_mask << 1) | bit;
                        ll total = left_val + right_val;

                        if (L == 1) {
                            // 达到 k 位，执行一次合并
                            int nc = merge_char[mask];
                            dp[l][r][nc] = max(dp[l][r][nc], total + merge_score[mask]);
                        } else {
                            // 尚未达到 k 位，直接保留拼接结果
                            dp[l][r][mask] = max(dp[l][r][mask], total);
                        }
                    }
                }
            }
        }
    }

    // 最终答案：整个串 [1, n] 压缩到最终长度后的最大得分
    int final_len = (n - 1) % (k - 1) + 1;
    ll ans = 0;
    for (int mask = 0; mask < (1 << final_len); ++mask) {
        ans = max(ans, dp[1][n][mask]);
    }
    cout << ans << '\n';

    return 0;
}
