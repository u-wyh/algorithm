#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 定义max和min函数
int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int f(char *a, int n, int x) {
    int s = 0;
    char a1 = a[x];
    char b2 = a[x + 1];
    int i;

    // 往前看
    for (i = x; i >= 0 && (a[i] == a1 || a[i] == 'w'); i--) {
        s++;
    }

    // 往后看
    for (i = x + 1; i < n && (a[i] == b2 || a[i] == 'w'); i++) {
        s++;
    }

    return s;
}

int main() {
    int ans = -1, n;
    char a[3000]; // 假设输入字符串长度不超过1000，为了处理循环复制，分配三倍空间

    scanf("%d%s", &n, a);
    int len = strlen(a);
    // 复制字符串以处理循环
    char temp[3000 * 3 + 1]; // +1 for the null terminator
    strcpy(temp, a);
    strcat(temp, a);
    strcat(temp, a);

    // 遍历中间的那一段
    for (int i = len; i < 2 * len; i++) {
        if (temp[i] == temp[i + 1]) {
            continue;
        }

        if (temp[i] == 'w') {
            temp[i] = 'r';
            ans = max(ans, f(temp, 3 * len, i));
            temp[i] = 'b';
            ans = max(ans, f(temp, 3 * len, i));
            temp[i] = 'w';
        }

        ans = max(ans, f(temp, 3 * len, i));
    }

    ans = min(ans, n); // 最长也不能比总长长
    if (ans == -1) {
        ans = n; // 出现这种情况必定是一路continue过来的
    }

    printf("%d\n", ans);
    return 0;
}
