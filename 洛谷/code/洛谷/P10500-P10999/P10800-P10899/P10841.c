// https://www.luogu.com.cn/problem/P10841
// 题意：给小写字符串 s，把它从头到尾分成若干非空连续段。
// 相邻两段作为字符串不能完全相同，输出最多能分几段。
// 数据范围：1 ≤ T ≤ 10^5，1 ≤ n ≤ 10^6，
// 同一测试点各组 n 之和至多 10^6。
// 算法标签：贪心、线性扫描

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
