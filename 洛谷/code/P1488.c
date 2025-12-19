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
