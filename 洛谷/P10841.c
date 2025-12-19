#include <stdio.h>
#include <string.h>

int main() {
    int t, n;
    char s[1001]; // 假设字符串长度不超过1000
    char last[2] = ""; // 记录上次选的字符，因为只处理单个字符，所以长度为2足够

    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        scanf("%d %s", &n, s);
        int cnt = n;

        // 初始化last为空字符串
        last[0] = '\0';

        for (int j = 0; s[j] != '\0'; j++) {
            if (last[0] != '\0' && s[j] == last[0]) {
                cnt--;
                j++; // 跳过当前字符，因为它与上一个字符相同
                // 更新last为当前字符和下一个字符的组合（但这里只处理单个字符，所以只更新为下一个字符）
                last[0] = s[j];
                last[1] = '\0'; // 确保字符串结束
            } else {
                // 不相等则记录当前字符
                last[0] = s[j];
                last[1] = '\0'; // 确保字符串结束
            }
        }

        printf("%d\n", cnt);
    }

    return 0;
}
