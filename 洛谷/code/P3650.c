// https://www.luogu.com.cn/problem/P3650
// 题意：输入山峰数量 n，以及各座山峰的整数海拔 a_1..a_n。
// 每次可将一座山峰的海拔增加或减少整数 x，花费为 x^2；要求修改后最高山峰与最低山峰的海拔差不超过 17。
// 输出需要支付的最小总花费。
// 数据范围：1 <= n <= 1000，0 <= a_i <= 100。
#include <stdio.h>
#include <stdlib.h>

int a[100001]; // 注意数组大小需要+1，因为索引从1开始
int n, minn, s = 1e9 + 1, sum;

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    // 使用qsort进行排序，需要包含stdlib.h和定义比较函数
    qsort(a + 1, n, sizeof(int), (int (*)(const void*, const void*))compare);


    for (int j = a[1]; j <= a[n]; j++) {
        sum = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] - j > 17) {
                sum += (a[i] - j - 17) * (a[i] - j - 17);
            }
            if (a[i] < j) {
                sum += (j - a[i]) * (j - a[i]); // 注意这里应该是j-a[i]，因为我们要削去的是低于j的部分
            }
        }
        s = (sum < s) ? sum : s; // 使用三元运算符进行最小值更新
    }

    printf("%d\n", s);
    return 0;
}
