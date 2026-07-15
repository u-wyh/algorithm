#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Key {
    int a[6];

    bool operator<(const Key& other) const {
        for (int i = 0; i < 6; i++) {
            if (a[i] != other.a[i]) return a[i] < other.a[i];
        }
        return false;
    }

    bool operator==(const Key& other) const {
        for (int i = 0; i < 6; i++) {
            if (a[i] != other.a[i]) return false;
        }
        return true;
    }
};

ll C[7][7];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<array<int, 6>> A(N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 6; j++) {
            cin >> A[i][j];
        }
    }

    // 预处理组合数
    for (int i = 0; i <= 6; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }

    // F[x] 表示：枚举所有大小为 x 的位置集合，
    // 有多少年份对在这些位置上完全相同。
    vector<ll> F(7, 0);

    // 空集合：任意两个年份都满足
    F[0] = 1LL * N * (N - 1) / 2;

    // 枚举 6 个位置的所有非空子集
    for (int mask = 1; mask < (1 << 6); mask++) {
        int cnt_pos = __builtin_popcount(mask);

        vector<Key> keys;
        keys.reserve(N);

        for (int i = 0; i < N; i++) {
            Key key{};
            int idx = 0;

            // 把当前子集中的位置提取出来，作为比较关键字
            for (int j = 0; j < 6; j++) {
                if (mask & (1 << j)) {
                    key.a[idx++] = A[i][j];
                }
            }

            // 剩余位置补 0，保证 Key 可以直接排序比较
            while (idx < 6) {
                key.a[idx++] = 0;
            }

            keys.push_back(key);
        }

        sort(keys.begin(), keys.end());

        // 统计相同 key 的数量，贡献 C(cnt, 2)
        for (int i = 0; i < N; ) {
            int j = i + 1;
            while (j < N && keys[j] == keys[i]) {
                j++;
            }

            ll cnt = j - i;
            F[cnt_pos] += cnt * (cnt - 1) / 2;

            i = j;
        }
    }

    // 容斥反推恰好 K 个位置相同的年份对数量
    //
    // F[m] = sum_{t=m}^{6} C(t, m) * Exact[t]
    //
    // 因此：
    // Exact[K] = sum_{m=K}^{6} (-1)^(m-K) * C(m, K) * F[m]
    ll ans = 0;

    for (int m = K; m <= 6; m++) {
        ll term = C[m][K] * F[m];

        if ((m - K) % 2 == 0) {
            ans += term;
        } else {
            ans -= term;
        }
    }

    cout << ans << '\n';

    return 0;
}