#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // 引入INT_MAX和INT_MIN，但在这个例子中我们不需要它们，因为我们直接使用long long的常量

int main() {
    int n;
    long long x = -1e10, y = 1e10;
    scanf("%d", &n); // 使用scanf代替cin

    for (int i = 1; i <= n; i++) {
        long long d;
        scanf("%lld", &d); // 使用%lld读取long long类型的数

        // 更新x和y的值
        if (d - y > x) {
            x = d - y;
        }
        if (d < y) {
            y = d;
        }
    }

    printf("%lld\n", x); // 使用printf代替cout，并添加换行符
    return 0;
}
