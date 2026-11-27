// https://www.luogu.com.cn/problem/P1280
// 题意：一天有 n 分钟，给 k 项任务的开始时间 p 和持续时间 t。
// 空闲时遇到任务开始，必须从同时开始的任务中挑一项做完，忙时开始的任务交给同事。
// 求一天内最多能空闲几分钟。
// 数据范围：1 ≤ n,k ≤ 10^4，1 ≤ p ≤ n，任务结束时间 p+t-1 在 [1,n]。
// 算法标签：动态规划、排序

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long int ks;
    long int js;
} ren;

int cmp(const void *a, const void *b) {
    ren *renA = (ren *)a;
    ren *renB = (ren *)b;
    return renB->ks - renA->ks; // 注意这里用减法实现降序排序
}

int main() {
    long int n, k, i, j, num = 1;
    long int sum[10001] = {0};
    long int f[10001] = {0};
    ren z[10001];

    scanf("%ld %ld", &n, &k);
    for (i = 1; i <= k; i++) {
        scanf("%ld %ld", &z[i].ks, &z[i].js);
        sum[z[i].ks]++;
    }

    qsort(z + 1, k, sizeof(ren), cmp); // 使用qsort进行排序

    for (i = n; i >= 1; i--) {
        if (sum[i] == 0) {
            f[i] = f[i + 1] + 1;
        } else {
            for (j = 1; j <= sum[i]; j++) {
                if (f[i + z[num].js] > f[i]) {
                    f[i] = f[i + z[num].js];
                }
                num++; // 当前已扫过的任务数
            }
        }
    }

    printf("%ld\n", f[1]);
    return 0;
}
