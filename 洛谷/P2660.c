#include <stdio.h>

int main() {
    long long x, y, ans = 0, temp;
    scanf("%lld %lld", &x, &y);

    while (x && y) { // 如果x和y都不为0，则继续循环
        // 交换x和y的值
        temp = x;
        x = y;
        y = temp;

        // 计算并累加当前可种植的最大正方形数量
        ans += 4 * y * (x / y);

        // 更新x的值为x除以y的余数
        x %= y;
    }

    // 输出结果
    printf("%lld\n", ans);

    return 0;
}
