// https://www.luogu.com.cn/problem/P10351
// 题意：给长度为 n 的整数序列，把所有元素划分到若干子序列中，可以不连续。每个子序列都要有一种数出现严格超过一半的次数，输出最少需要划分成几组。
// 数据范围：1 ≤ n ≤ 5 × 10^5，1 ≤ a[i] ≤ n。
// 算法标签：计数统计、贪心、排序

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int tot;
} num;

// 比较函数，用于qsort
int compare(const void *a, const void *b) {
    num *numA = (num *)a;
    num *numB = (num *)b;
    // 注意，这里与C++中的运算符重载相反，因为qsort需要返回负数、零或正数
    if (numA->tot > numB->tot) return -1;
    if (numA->tot < numB->tot) return 1;
    return 0;
}

int main() {
    int n, tot = 0, ans = 0;
    scanf("%d", &n);
    num cnt[500001] = {0}; // 初始化数组

    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        if (!cnt[x].tot) tot++;
        cnt[x].tot++;
    }

    // 使用qsort进行排序
    qsort(cnt + 1, n, sizeof(num), compare);

    // 重新计算tot，因为qsort会打乱原数组，但在这里我们不需要，只是用n代替tot进行后续计算
    tot = n;

    for (int i = 1; i <= n; ++i) {
        if (cnt[i].tot * 2 - 1 >= tot) {
            ans++;
            break;
        }
        ans++;
        tot -= cnt[i].tot * 2 - 1;
    }

    printf("%d\n", ans);

    return 0;
}
