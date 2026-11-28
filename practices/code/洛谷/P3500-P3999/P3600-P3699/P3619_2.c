// https://www.luogu.com.cn/problem/P3619
// 题意：输入测试点数 Z，每个测试点给出任务数 n、初始时间 T，
// 以及 n 个任务的限制 t_i 与时间增量 b_i。
// 按任意顺序依次完成这 n 个任务，执行第 i 个任务要求当前 T > t_i，
// 完成后 T 变为 T + b_i，且任何时刻必须保证 T > 0。
// 若能完成全部 n 个任务输出 +1s，否则输出 -1s。
// 数据范围：
// Z <= 10，n <= 10^5，t_i <= 10^5，T <= 10^5，
// -10^5 <= b_i <= 10^5。
// 难度评分：1600（洛谷分级换算）
// 算法标签：贪心、排序
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 2147483647

typedef struct {
    int tim;
    int b;
} node;

typedef struct {
    int tim;
    int b;
} ss;

int cmp(const void *a, const void *b) {
    node *na = (node *)a;
    node *nb = (node *)b;
    return na->tim - nb->tim; // 由于b大于0，所以先做t小的任务
}

int comp(const void *a, const void *b) {
    ss *sa = (ss *)a;
    ss *sb = (ss *)b;
    // 注意这里返回的是逆序，因为qsort默认是升序，我们需要降序
    return (sb->b + sb->tim) - (sa->b + sa->tim);
}

int main() {
    int z;
    scanf("%d", &z);
    for (int i = 0; i < z; i++) {
        int n, t;
        scanf("%d%d", &n, &t);
        node a[100010] = {0};
        ss f[100010] = {0};
        int cnt = 0, num = 0;

        for (int j = 0; j < n; j++) {
            int x, y;
            scanf("%d%d", &x, &y);
            if (y > 0) {
                a[cnt].tim = x;
                a[cnt].b = y;
                cnt++;
            } else {
                f[num].tim = x;
                f[num].b = y;
                num++;
            }
        }

        qsort(a, cnt, sizeof(node), cmp);
        qsort(f, num, sizeof(ss), comp);

        int s = 0;
        for (int j = 0; j < cnt; j++) {
            if (t > a[j].tim) {
                t += a[j].b;
            } else {
                s = 1;
                break;
            }
        }

        for (int j = 0; j < num; j++) {
            if (t > f[j].tim) {
                t += f[j].b;
            } else {
                s = 1;
                break;
            }
            if (t <= 0) {
                s = 1;
                break;
            }
        }

        if (s == 0) {
            printf("+1s\n");
        } else {
            printf("-1s\n");
        }
    }
    return 0;
}
