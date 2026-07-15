#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using u128 = unsigned __int128;

const int MAXN = 55;

// 数字数量
int n;

// 当前递归路径上，每个数字剩余的上界
ull m[MAXN];

// 当前位为 1 的上界，在选择当前位为 1 后的低位取值数量
ull value[MAXN];

// dp[q] 表示恰好有 q 个数字变为自由数时，
// 其余受限数字的低位取值数量乘积之和
u128 dp[MAXN];

// 计算满足异或和为 0 且不全为 0 的序列数量
ull solve() {
    u128 total = 0;
    bool alive = true;

    for (int bit = 31; bit >= 0 && alive; --bit) {
        ull bitValue = 1ULL << bit;

        // 当前位上界为 1 的数字数量
        int cnt = 0;

        // 当前位上界为 0 的数字，其低位取值数量乘积
        u128 fixedProduct = 1;

        for (int i = 1; i <= n; ++i) {
            if (m[i] & bitValue) {
                ++cnt;

                // 当前位选择 1 后，低位范围为 [0, m[i] - 2^bit]
                value[cnt] = m[i] - bitValue + 1;
            } else {
                fixedProduct *= m[i] + 1;
            }
        }

        memset(dp, 0, sizeof(dp));
        dp[0] = 1;

        for (int i = 1; i <= cnt; ++i) {
            for (int q = i; q >= 1; --q) {
                // 当前数字选择 1，继续受限
                dp[q] *= value[i];

                // 当前数字选择 0，变为自由数
                dp[q] += dp[q - 1];
            }

            dp[0] *= value[i];
        }

        for (int q = 1; q <= cnt; ++q) {
            // 当前位选择 1 的数量为 cnt - q，必须为偶数
            if ((cnt - q) % 2 == 0) {
                int exponent = bit * (q - 1);
                u128 freeWays = (u128)1 << exponent;

                total += fixedProduct * dp[q] * freeWays;
            }
        }

        // 所有当前位为 1 的数字都选择 1 时，
        // 只有 cnt 为偶数才能继续处理低位
        if (cnt % 2 == 1) {
            alive = false;
        } else {
            for (int i = 1; i <= n; ++i) {
                if (m[i] & bitValue) {
                    m[i] -= bitValue;
                }
            }
        }
    }

    // 如果递归路径能够处理完所有位，
    // 说明原始的 m_1 xor ... xor m_n 等于 0，
    // 此时序列 a_i = m_i 还需要计入
    if (alive) {
        ++total;
    }

    // 去除全为 0 的序列
    --total;

    return (ull)total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> m[i];
    }

    cout << solve() << '\n';

    return 0;
}