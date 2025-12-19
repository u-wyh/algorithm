#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COMPANIES 102

int a[MAX_COMPANIES][MAX_COMPANIES]; // a[i][j]表示公司i拥有公司j百分之a[i][j]的股份
int cnt[MAX_COMPANIES]; // cnt[i]表示当前阶段中公司x拥有公司i累计有百分之cnt[i]的股份
int m;
int f[MAX_COMPANIES]; // f[i]表示当前阶段中第i个公司是否被搜索过
int own[MAX_COMPANIES]; // own[i]表示当前阶段中公司x是否能控制公司i

void EMILY(int x) {
    if (f[x]) // 边界条件，如果当前公司已被搜索过，则直接返回
        return;
    f[x] = 1; // 标记为搜索过
    for (int i = m; i > 0; i--) // 枚举所有公司
    {
        cnt[i] += a[x][i]; // 加上当前公司的股份百分点
        if (cnt[i] > 50) { // 满足条件
            own[i] = 1; // 设置为能够控制
            EMILY(i); // 递归
        }
    }
}

int main() {

    int i, j, u, v, w, n;

    // 初始化m为0
    m = 0;

    for (scanf("%d", &n); n; n--) {
        scanf("%d%d%d", &u, &v, &w);
        a[u][v] = w; // 公司u拥有公司v百分之w的股份
        m = (m > u) ? m : u;
        m = (m > v) ? m : v;
    }

    for (i = 1; i <= m; i++) {
        memset(f, 0, sizeof(f)); // 把遍历情况全部清空
        memset(own, 0, sizeof(own)); // 把所属情况全部置为0
        memset(cnt, 0, sizeof(cnt)); // 把累计百分点全部清零
        EMILY(i); // 从第i个公司开始搜索
        for (j = 1; j <= m; j++)
            if (own[j] && i != j) // 如果公司j属于公司i且i不等于j
                printf("%d %d\n", i, j); // 输出公司i控制公司j
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}
