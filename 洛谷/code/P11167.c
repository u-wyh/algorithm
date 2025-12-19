#include <stdio.h>
#include <stdlib.h>

int n, ti[5001];
int day[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 31, 30}; // 12个月加上一个额外的0作为索引
int a[5], b[5]; // 两个数组存储日期和时间
long long t; // 分钟
int ans; // 答案

int is_leap_year(int year) {
    if (year % 100 == 0) {
        return (year % 400 == 0);
    }
    return (year % 4 == 0);
}

int cmp(const void *a,const void *b)
{
    return (*(int *)a-*(int *)b);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) { // 注意C语言数组从0开始
        scanf("%d", &ti[i]);
    }
    qsort(ti, n, sizeof(int), (int (*)(const void *, const void *))cmp); // 需要定义cmp函数进行排序

    scanf("%d-%d-%d-%d:%d", &a[0], &a[1], &a[2], &a[3], &a[4]);
    scanf("%d-%d-%d-%d:%d", &b[0], &b[1], &b[2], &b[3], &b[4]);

    for (int i = a[0]; i < b[0]; i++) {
        if (is_leap_year(i)) {
            t -= 366;
        } else {
            t -= 365;
        }
    }

    for (int i = 0; i < a[1] - 1; i++) { // 月份从1开始，但数组索引从0开始
        t += day[i];
    }

    for (int i = 0; i < b[1] - 1; i++) {
        t -= day[i];
    }

    if (is_leap_year(a[0]) && a[1] > 2) {
        t++; // 如果是闰年且月份大于2，需要加上2月多出的那一天
    }

    if (is_leap_year(b[0]) && b[1] > 2) {
        t--; // 类似地，如果是闰年且结束月份大于2，需要减去2月多出的那一天
    }

    t += a[2]; // 加上开始的日
    t -= b[2]; // 减去结束的日

    t *= 1440; // 转换为分钟
    t += 60 * a[3] + a[4]; // 加上开始的分钟和秒
    t -= 60 * b[3] + b[4]; // 减去结束的分钟和秒

    t = -t; // 反转时间差

    for (int i = 0; i < n; i++) {
        if (t >= ti[i]) {
            t -= ti[i];
            ans++;
        } else {
            break;
        }
    }

    printf("%d\n", ans); // 输出答案
    return 0;
}
