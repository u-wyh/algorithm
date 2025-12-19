#include<string.h>
#include<stdio.h>
#include<stdlib.h>

// 定义max和min函数
int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n;
    char s[700], c;
    int a = 0, b = 0, w = 0, ans = 0;

    scanf("%d%s", &n, s);

    // 复制字符串以处理循环
    char temp[700 * 2];
    memcpy(temp, s, n);
    memcpy(temp + n, s, n);

    // 初始化c为第一个字符
    c = s[0];

    // 遍历两倍长度的字符串
    for (int i = 0; i < n * 2; i++) {
        if (temp[i] == 'w') {
            b++;
            w++;
        } else if (temp[i] == c) {
            b++;
            w = 0;
        } else {
            ans = max(ans, a + b);
            a = b - w;
            b = w + 1;
            w = 0;
            c = temp[i];
        }
    }

    // 最后一次更新ans
    ans = max(ans, a + b);

    // 输出结果，但不超过n
    printf("%d\n", min(ans, n));

    return 0;
}
