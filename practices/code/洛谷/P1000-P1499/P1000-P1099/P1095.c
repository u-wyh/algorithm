// https://www.luogu.com.cn/problem/P1095
// 题意：初始有 M 点魔法，出口在 S 米外，最多有 T 秒。
// 每秒可跑 17 米、花 10 点魔法闪烁 60 米，或留在原地恢复 4 点魔法。
// 若能逃出，输出 Yes 和最短时间，否则输出 No 和 T 秒内最远距离。
// 数据范围：0 ≤ M ≤ 1000，1 ≤ S ≤ 10^8，
// 1 ≤ T ≤ 300000。
// 难度评分：1300（洛谷分级换算）
// 算法标签：贪心、动态规划

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main() {
    int m, s, t, now = 0;
    scanf("%d %d %d", &m, &s, &t);
    int s1 = 0, s2 = 0; // 存放跑步能走的距离和用闪烁能走的距离
    for (int i = 1; i <= t; i++) { // 一个个时间去推
        s1 += 17; // 闪现和跑步分批进行
        if (m >= 10) {
            s2 += 60;
            m -= 10; // 能够闪现这肯定要闪现的
        } else {
            m += 4; // 没蓝这一回合就用来回蓝
        }
        if (s2 > s1) {
            s1 = s2; // 闪现的快了就把跑步的替换成闪现的
        }
        if (s1 >= s) { // 跑出去了就输出当前时间
            printf("Yes\n%d\n", i);
            return 0;
        }
    }
    printf("No\n%d\n", s1); // 时间都用完了还没跑出去，输出“No”和s1的值
    return 0;
}
