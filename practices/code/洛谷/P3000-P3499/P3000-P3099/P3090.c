// https://www.luogu.com.cn/problem/P3090
// 题意：输入环形牛栏数 N（编号 0 到 N-1）和描述行数 K，
// 每行给出 X, Y, A, B。
// 每行表示有 Y 批牛，第 i 批（1 <= i <= Y）有 X 头牛，
// 它们心仪的牛栏号为 (A*i + B) mod N。
// 每头牛依次去心仪牛栏，
// 若已被占就顺时针往后找第一个空牛栏（N-1 之后接 0）并占用。
// 求所有牛占好位置后，剩余空牛栏中编号最小的那个（与进入顺序无关）。
// 输出一个整数表示最小空牛栏编号。
// 数据范围：2 <= N <= 3*10^6，1 <= K <= 10^4，
// 0 <= A, B <= 10^9，奶牛总数不超过 N-1
// 空间限制 64 MB。
// 难度评分：1100（洛谷分级换算）
// 算法标签：模拟
#include <stdio.h>

#define int long long

#define N 3000000

int n;
int ans[N];
int x, y, a, b, k;

int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int main() {
    n = read();
    k = read();
    while (k--) {
        x = read();
        y = read();
        a = read();
        b = read();
        for (int i = 1; i <= y; i++) {
            ans[(a * i + b) % n] += x;
        }
    }
    for (int i = 0; i < n; i++) {
        if (ans[i] > 0) {
            ans[(i + 1) % n] += ans[i] - 1;
            ans[i] = 1;
        }
    }
    while (ans[0] > 1) {
        for (int i = 0; i < n; i++) {
            if (ans[i] > 0) {
                ans[(i + 1) % n] += ans[i] - 1;
                ans[i] = 1;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (ans[i] == 0) {
            printf("%lld\n", i);
            return 0;
        }
    }
    return 0;
}
