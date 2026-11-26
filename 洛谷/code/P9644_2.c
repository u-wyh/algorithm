// https://www.luogu.com.cn/problem/P9644
// 题意：多组数据（共 T 组）。
// 有 n 盏灯排成一排，给定长度为 n 的 01 串表示初始亮灭（1 亮，0 灭，至少有一个 1）。
// 每次操作可将连续 L 盏灯全部关闭（长度为固定的正整数 L，覆盖 [i, i+L-1]）。
// 求能在 k 次操作内关掉所有灯的最小正整数 L。
// 题意：第一行输入 T，每组输入 n, k 及 01 串 s；每组输出一行一个整数。
// 数据范围：1 <= k <= n <= 2 * 10^5，sum(n) <= 2 * 10^6（未显式给出 T 上界，受 sum(n) 限制）。
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int n, k;
char s[200005];

bool check(int x) {
    int p = 0;
    for (int i = 1; i <= n; i++) {
        if (s[i] == '1') {
            p = i; // 找到第一个'1'
            break;
        }
    }
    int cnt = 0; // 记录段数
    while (p <= n) {
        p += x;
        cnt++;
        if (p > n) break; // 控制边界
        while (s[p] == '0') p++; // 如果是'0'则无需覆盖
    }
    if (cnt <= k) return true; // 符合条件
    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &n, &k);
        scanf("%s", s + 1); // 从s[1]开始读入字符串，s[0]未使用
        int l = 1; // 左端点设为1
        int r = n / k + 1; // 假设每个段都尽可能短

        while (l < r) { // 二分答案
            int mid = (l + r) / 2;
            if (check(mid)) r = mid;
            else l = mid + 1;
        }
        printf("%d\n", l);
    }
    return 0;
}
