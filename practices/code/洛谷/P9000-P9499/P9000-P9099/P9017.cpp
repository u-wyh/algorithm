// https://www.luogu.com.cn/problem/P9017
// 题意：T 组询问，每组给定长 N 的 01 串 a, b。
// 每次操作先翻转 b 中某一位，再对 b 中所有为 1 的位置翻转 a 的对应位，
// 最后将 b 循环右移 1 位。
// 求使 a 全变为 0 的最少操作次数。
// 数据范围：1 <= T <= 2*10^5，2 <= N <= 20。
// 难度评分：2000（洛谷分级换算）
// 算法标签：状态压缩动态规划、位运算
#include <iostream>
using namespace std;
string s,t;
int T, n;
int g[45][22], mask[22];
bool f[45][1 << 21];

int calc (int s, int t) {
    if (s == 0) return 0;
    for (int i = 1; i <= 2 * n; i ++) {
        int vis = s;
        for (int j = 0; j < n; j ++) if (t & (1 << j) ) vis = vis ^ g[i][j];
        if (f[i][vis]) return i;
    }
}

int main() {
    f[0][0] = 1;
    cin >> T >> n;
    for (int i = 0; i <= n; i ++) mask[i] = 1 << i;
    int N = 1 << n;
    for (int k = 0; k < n; k ++)
        for (int i = 1; i <= 2 * n; i ++)
            for (int j = 0; j < i; j ++) g[i][k] ^= mask[(k + j) % n];
    for (int i = 1; i <= 2 * n; i ++) for (int j = 0; j < N; j ++) {
            if (!f[i - 1][j]) continue;
            for (int k = 0; k < n; k ++){
                int vis = j;
                vis ^= g[i][k];
                f[i][vis] = 1;
            }
        }
    while (T --){
        cin >> s >> t;
        int S = 0, T = 0;
        for (int i = 0; i < n; i ++) {
            if (s[i] == '1') S ^= (1 << i);
            if (t[i] == '1') T ^= (1 << i);
        }
        cout << calc(S, T) << "\n";
    }
    return 0;
}