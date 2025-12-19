#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

int n, m, tot, ans, le, maxlen = -1e9;
int a[MAXN], len[MAXN], f[MAXN];
char s[MAXN];

// 辅助函数，用于计算两个整数中的较大值
int max(int x, int y) {
    return (x > y) ? x : y;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d %s", &m, s);

    // 预处理字符串
    for (int i = 0; i < m - 2; i++) {
        if (s[i] == 'a' && s[i + 1] == 'b' && s[i + 2] == 'c') {
            le++;
            i += 2;
        } else if (le > 0) {
            len[++tot] = le;
            le = 0;
            maxlen = (maxlen > len[tot]) ? maxlen : len[tot];
        }
    }
    if (le > 0) {
        len[++tot] = le;
        maxlen = (maxlen > len[tot]) ? maxlen : len[tot];
    }

    // 初始化dp数组
    memset(f, 0, sizeof(f));

    // 动态规划求解
    for (int i = 1; i <= maxlen; i++) {
        for (int k = max(i - n, 0); k < i; k++) {
            f[i] = (f[i] > f[k] + a[i - k]) ? f[i] : f[k] + a[i - k];
        }
    }

    // 计算总得分
    for (int i = 1; i <= tot; i++) {
        ans += f[len[i]];
    }

    printf("%d\n", ans);

    return 0;
}

