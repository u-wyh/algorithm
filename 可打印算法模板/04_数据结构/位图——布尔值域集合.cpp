// 用途：用位图维护 0..n-1 中哪些整数已出现，支持设置、清除、翻转和查询。
// 时间：初始化 O(n/32)，单次操作 O(1)。
// 空间：O(n/32)。
// 注意：n≤1000000，查询下标必须在 0..n-1；用无符号位避免左移到第 31 位时未定义行为。
// 题意：操作 1 x 设置为存在，2 x 清除，3 x 翻转，4 x 输出当前是否存在。
// 思路：每个 uint32_t 存 32 个标记，商定位字，余数定位位。
#include <bits/stdc++.h>
using namespace std;

const int MAXU = 1000000;

class Bitset {
public:
    // 下标除以 32 找字，余数找该字中的位。
    uint32_t word[(MAXU + 31) / 32];

    void init(int n) {
        fill(word, word + (n + 31) / 32, 0U);
    }

    void add(int num) {
        word[num / 32] |= 1U << (num % 32);
    }

    void remove(int num) {
        word[num / 32] &= ~(1U << (num % 32));
    }

    void reverse(int num) {
        // 异或 1 只翻转目标位。
        word[num / 32] ^= 1U << (num % 32);
    }

    bool contains(int num) const {
        return (word[num / 32] >> (num % 32)) & 1U;
    }
};

Bitset bits;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    bits.init(n);
    while (q--) {
        int op, x;
        cin >> op >> x;
        if (op == 1) bits.add(x);
        else if (op == 2) bits.remove(x);
        else if (op == 3) bits.reverse(x);
        else cout << bits.contains(x) << '\n';
    }
    return 0;
}
