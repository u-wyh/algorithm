#include <stdio.h>

char s[800010];

int main() {
    int n, S = 0;
    scanf("%d%s", &n, s); // 注意这里%s不会限制输入长度，实际使用时可能需要更安全的输入方式

    // 遍历字符串s中的每个字符，计算它们的ASCII值之和（这里假设只包含数字字符）
    for (int i = 0; i < 8 * n; i++) {
        S += s[i] - '0';
    }

    // 判断S是否在3n到6n之间
    if (S < 3 * n || S > 6 * n) {
        printf("NIE\n");
        return 0;
    }

    int x[4] = {0}; // 初始化x数组
    x[3] = (S - 3 * n) / 3; // 计算o的数量
    x[S % 3] = 1; // 标记出现次数为奇数的字符（a, c, g中的一个）
    x[0] = n - x[3] - x[2] - x[1]; // 剩下的都是a

    // 输出结果
    while (x[0]--) printf("a");
    if (x[1]) while (x[1]--) printf("c"); // 如果c的数量不为0，则输出c
    if (x[2]) while (x[2]--) printf("g"); // 如果g的数量不为0，则输出g
    while (x[3]--) printf("o");

    return 0;
}

// 注意：上述代码中的输入处理（scanf("%d%s", &n, s);）可能存在安全隐患，
// 因为%s不会检查目标数组的大小，可能会导致缓冲区溢出。
// 在实际应用中，建议使用更安全的方式来读取字符串，如fgets()等。
