#include <stdio.h>

int n, a[15];

int main() {
    scanf("%d", &n); // 读取n的值
    for (int i = 0; i < n; i++) { // 注意数组索引从0开始
        scanf("%d", &a[i]); // 读取数组元素
    }

    for (int i = 1; i < n; i++) { // 从第二个元素开始检查
        if (a[i] != a[i - 1] + 1) { // 检查是否不是连续递增
            printf("%d\n", a[i]); // 输出第一个不连续递增的元素
            return 0; // 退出程序
        }
    }

    printf("-1\n"); // 如果所有元素都是连续递增的，则输出-1
    return 0;
}
