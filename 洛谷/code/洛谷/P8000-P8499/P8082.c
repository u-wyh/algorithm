// https://www.luogu.com.cn/problem/P8082
// 题意：给定无前导 0 的 N 位正整数，
// 从中删除恰好 K 位数字（其余数字保持原有相对顺序），
// 求剩下的 N - K 位数的最大值。
// 第一行输入 N, K，第二行输入该 N 位数。
// 输出一行表示最大结果。
// 数据范围：1 <= K < N <= 5*10^5。
// 算法标签：单调栈、贪心
#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005

char s[MAXN];
int st[MAXN], top = 0;

int main() {
    int n, k;
    scanf("%d%d%s", &n, &k, s + 1); // 注意s+1，因为数组索引从1开始读取

    for (int i = 1; i <= n; i++) {
        int x = s[i] - '0'; // 将字符转换为整数
        while (k && top && st[top] < x) {
            k--;
            st[top--] = 0; // 弹出操作
        }
        st[++top] = x; // 加入操作
    }

    // 遍历栈，不遍历后面剩余的k个数
    for (int i = 1; i <= top - k; i++) {
        printf("%d", st[i]);
    }
    return 0;
}
