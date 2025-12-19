#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 100010
#define INF 1000000000

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

char s[N], ans[N];
int n, a, b;

void dfs(int k, int c, int d, char *str) {
    if (k == n) {
        if (strcmp(str, ans) > 0) { // 字符串比较，取字典序较大的
            strcpy(ans, str);
        }
        return;
    }
    int x = 9 - (str[k] - '0'), y = str[k] - '0' + 1;
    if (c + x <= a && d + y <= b) {
        str[k] = '9';
        dfs(k + 1, c + x, d, str);
        str[k] = str[k] - 1 + '0'; // 回溯
        dfs(k + 1, c, d + y, str);
    } else if (c + x <= a) {
        str[k] = '9';
        dfs(k + 1, c + x, d, str);
        str[k] = str[k] - 1 + '0'; // 回溯
    } else if (d + y <= b) {
        str[k] = '9';
        dfs(k + 1, c, d + y, str);
        str[k] = str[k] - 1 + '0'; // 回溯
    } else {
        str[k] += a - c;
        dfs(k + 1, a, d, str);
        // 注意：这里不需要对str[k]进行回溯，因为它已经被设置为最大可能值
    }
}

int main() {
    scanf("%s", s);
    strcpy(ans, s);
    n = strlen(s);
    a = read();
    b = read();
    dfs(0, 0, 0, s);
    printf("%s\n", ans);
    return 0;
}
