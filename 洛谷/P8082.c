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
