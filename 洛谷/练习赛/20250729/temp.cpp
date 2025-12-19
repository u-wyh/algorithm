#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    // 最大位数（31位，覆盖0到30位）
    const int MAX_BIT = 31;
    // 存储每个数当前低k位的popcount（0~k-1位）
    vector<int> cur_pop(n, 0);
    long long ans = 0;

    // 遍历每一位（从最低位0到最高位30）
    for (int k = 0; k < MAX_BIT; k++) {
        // 统计四种状态的数量
        // 状态格式: (当前位值 << 1) | (低k位popcount的奇偶性)
        // state 0: 当前位0, 奇偶性0
        // state 1: 当前位0, 奇偶性1
        // state 2: 当前位1, 奇偶性0
        // state 3: 当前位1, 奇偶性1
        vector<long long> cnt(4, 0);

        // 遍历数组中的每个数
        for (int i = 0; i < n; i++) {
            // 获取当前数的第k位
            int bit = (A[i] >> k) & 1;
            // 获取低k位popcount的奇偶性（0:偶数, 1:奇数）
            int parity = cur_pop[i] & 1;
            // 组合状态
            int state = (bit << 1) | parity;
            cnt[state]++;

            // 更新cur_pop: 如果当前位为1，则popcount加1
            if (bit) {
                cur_pop[i]++;
            }
        }

        // 计算满足条件的配对数量
        // 配对规则: 
        //   state0 (0,0) 与 state2 (1,0) 配对（当前位不同，奇偶性相同）
        //   state1 (0,1) 与 state3 (1,1) 配对（当前位不同，奇偶性相同）
        long long pairs = cnt[0] * cnt[2] + cnt[1] * cnt[3];
        
        // 累加当前位的贡献：配对数量 * 2^k
        ans += pairs * (1LL << k);
    }

    cout << ans << endl;
    return 0;
}