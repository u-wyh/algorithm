// 用途：静态字符串预处理后，快速判断两个任意子串是否相等。
// 时间：预处理 O(n)，每次比较 O(1)。
// 空间：O(n)。
// 注意：下标从 1 开始、区间闭合；n≤1000000；64 位哈希有极小碰撞概率。
// 题意：输入字符串和若干组 l1 r1 l2 r2，逐组判断两个子串是否相同。
// 思路：随机选奇数进制，前缀哈希相减消去前面字符；无符号溢出即模 2^64。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
char s[MAXN];
uint64_t powerBase[MAXN], prefixHash[MAXN], base;

void build(int n) {
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    base = (rng() % (1ULL << 32)) + (1ULL << 32);
    base |= 1ULL; // 奇数进制，避免低位过早退化。
    powerBase[0] = 1;
    for (int i = 1; i <= n; ++i) {
        powerBase[i] = powerBase[i - 1] * base;
        prefixHash[i] = prefixHash[i - 1] * base + (unsigned char)s[i] + 1;
    }
}

uint64_t getHash(int l, int r) {
    // 先把前缀 [1,l-1] 左移 r-l+1 位，再从 [1,r] 中减掉。
    return prefixHash[r] - prefixHash[l - 1] * powerBase[r - l + 1];
}

bool sameSubstring(int l1, int r1, int l2, int r2) {
    return r1 - l1 == r2 - l2 && getHash(l1, r1) == getHash(l2, r2);
}

int main() {
    scanf("%1000000s", s + 1);
    int n = strlen(s + 1);
    build(n);
    int q;
    scanf("%d", &q);
    while (q--) {
        int l1, r1, l2, r2;
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        puts(sameSubstring(l1, r1, l2, r2) ? "YES" : "NO");
    }
    return 0;
}
