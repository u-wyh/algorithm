// https://www.luogu.com.cn/problem/P1488
// 题意：给一个已被对角线划成三角形的凸多边形，第一个输入的三角形是黑色。
// 两人轮流沿已有对角线切下一个三角形，切下黑色三角形者胜。
// 假设双方最优，先手能赢输出 JMcat Win，否则输出 PZ Win。
// 数据范围：4 ≤ n ≤ 50000，顶点编号 0 到 n-1，
// 共给 n-2 个三角形。
// 难度评分：1200（洛谷分级换算）
// 算法标签：博弈论

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int a[3];
} tri;

tri h[50000 + 5];
bool point[50000 + 5];

int main() {
    int n;
    scanf("%d", &n);

    // 读取三角形顶点，注意最后一个三角形不需要读取
    for (int i = 0; i < n - 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            scanf("%d", &h[i].a[j]);
        }
    }

    // 初始化第一个三角形的顶点为已访问
    for (int j = 0; j < 3; ++j) {
        point[h[0].a[j]] = true;
    }

    short ans = 0;

    // 遍历每个三角形（除了第一个）
    for (int i = 1; i < n - 2; ++i) {
        int _ans = 0;

        // 统计当前三角形中有多少个顶点已被访问
        for (int j = 0; j < 3; ++j) {
            if (point[h[i].a[j]]) {
                _ans++;
            }
        }

        // 如果有两个顶点已被访问，则增加答案计数
        if (_ans == 2) {
            ++ans;
        }
    }

    // 根据题目要求输出结果
    if (ans == 1) {
        printf("JMcat Win\n");
    } else if (ans == 2) {
        if (n % 2) {
            printf("PZ Win\n");
        } else {
            printf("JMcat Win\n");
        }
    } else {
        if (n % 2) {
            printf("PZ Win\n");
        } else {
            printf("JMcat Win\n");
        }
    }

    return 0;
}
