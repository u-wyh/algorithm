#include <stdio.h>

int n, p[11] = {1}, cnt = 1, m;

void print(int aa) { // 输出方案
    for (int i = 1; i < aa; i++) {
        printf("%d+", p[i]);
    }
    printf("%d\n", p[aa]);
}

void dfs(int a) { // 通过DFS得到排列，a是当前的深度
    for (int i = p[a - 1]; i <= m; i++) { // 从前一个数的下一个数开始尝试
        if (i == n) continue; // 防止最后一行输出n（这里可能是为了避免不必要的搜索，因为n不能作为拆分的一部分，除非n本身就是拆分的一个数）
        p[a] = i;
        m -= i;
        if (m == 0) {
            print(a); // m减完时，该方案已排列完毕，进行输出
        } else {
            dfs(a + 1); // 否则继续搜索
        }
        m += i; // 回溯
    }
}

int main() {
    scanf("%d", &n);
    m = n;
    dfs(1);
    return 0;
}
