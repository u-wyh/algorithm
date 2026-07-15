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
