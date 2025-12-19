#include <stdio.h>

int m, n, q;

// 当前操作者为p, p为0时代表Stan操作, p为1时代表Ollie操作。
int find(int x, int y, int p) {
    if (x == y) return p; // 返回胜者
    if (y / x >= 2) return p; // 返回胜者
    else return find(y - x, x, p ^ 1); // 向下一个状态查找
}

int main() {
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        scanf("%d %d", &m, &n);
        if (m > n) {
            int temp = m;
            m = n;
            n = temp;
        }
        if (find(m, n, 0) == 0) {
            printf("Stan wins\n"); // 如果返回0, 胜者为Stan
        } else {
            printf("Ollie wins\n"); // 反之则为Ollie
        }
    }
    return 0;
}
