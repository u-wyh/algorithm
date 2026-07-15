#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_BAMBOO 200005

typedef long long LL;

LL data[MAX_BAMBOO]; // 存储竹子的高度
int p[MAX_BAMBOO] = {0}; // 存储竹子还能被砍伐的次数

int main() {
    int n;
    int Max = 0; // 最高的竹子要被砍几次
    LL cnt = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%lld", &data[i]);
        LL t = data[i];
        while (t > 1) { // 注意，t 从 1 开始将不再被砍伐，因为题目中的 while 循环条件是 t-1
            p[i]++;
            t = (LL)sqrt((double)(t / 2 + 1)); // 注意类型转换和精度问题
        }
        if (p[i] > Max) {
            Max = p[i];
        }
    }

    for (int i = Max; i > 0; i--) {
        for (int j = 0; j < n - 1; j++) { // 注意 j < n - 1 以避免数组越界
            if (p[j] == i) {
                if (data[j] != data[j + 1]) { // 当两个高度不一样的时候才计数
                    cnt++;
                }
                p[j]--; // 被砍伐了一次，可砍伐次数减一
                data[j] = (LL)sqrt((double)(data[j] / 2 + 1)); // 被砍伐了，用公式计算被砍伐后的高度
            }
        }
    }

    printf("%lld\n", cnt);
    return 0;
}
