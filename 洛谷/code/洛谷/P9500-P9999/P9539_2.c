// https://www.luogu.com.cn/problem/P9539
// 题意：给定长度为 n 的小写字母串 s 及整数 l, r。
// 构造一个长度为 n 的小写字母串 t，
// 使得满足 s_i = t_i 的位置数量在 [l, r] 之间
// 且 t 的字典序尽可能小（保证 0 <= l <= r <= n，恒有解）。
// 题意：第一行输入 n, l, r，第二行输入字符串 s；输出一行一个字符串 t。
// 数据范围：1 <= n <= 10^6，0 <= l <= r <= n。
// 算法标签：贪心、构造
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ll long long

// 自定义的读入函数，模仿C++的read
ll read() {
    ll x = 0, y = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') y = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch & 15);
        ch = getchar();
    }
    return x * y;
}

int main() {
    int n, l, r;
    char s[1000007]; // 假设字符串最大长度为1000006（因为最后一个字符是'\0'）
    bool fuck[1000007] = {0}; // 使用bool数组来标记已经变成'a'的位置

    n = read();
    l = read();
    r = read();

    // 将l和r转换为从字符串末尾开始计算的索引
    l = n - l;
    r = n - r;

    // 读取字符串
    scanf("%s", s);

    int flag = 0;
    for (int i = 0; i < n; i++) {
        if (flag == l) break;
        if (s[i] != 'a') {
            s[i] = 'a';
            flag++;
        } else {
            fuck[i] = true;
        }
    }

    // 如果还需要更多的'a'或者'b'来达到r
    if (flag < r) {
        for (int i = n - 1; i >= 0; i--) {
            if (fuck[i]) { // 只修改那些之前已经是'a'的位置
                s[i] = 'b';
                flag++;
                if (flag == r) break;
            }
        }
    }

    // 输出结果
    printf("%s\n", s);

    return 0;
}
