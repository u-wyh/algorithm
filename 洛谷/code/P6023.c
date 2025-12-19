#include <stdio.h>
#include <stdlib.h>

long long n, m, k; // 注意：因为数据非常大，所以每一个数据都得开long long，不然会溢出
long long a, b, s;
long long c[99999999]; // 观察数据范围，不想RE就开大点数组
long long maxn = 0; // 用来记录最大值

int main() {
    scanf("%lld %lld %lld", &n, &m, &k); // 输入相关数据
    for (int i = 0; i < k; i++) { // 分别输入每一个激励措施（注意数组从0开始）
        scanf("%lld %lld", &a, &b);
        if (n - b > 0) { // 判断是否能拿到积分
            if (a <= m) { // 确保a在有效天数内
                c[a - 1] += (n - b); // 存储这一天可拿积分，C语言数组从0开始
            }
        }
    }
    for (int i = 0; i < m; i++) { // 注意是要在有限天数m内查找
        if (c[i] > maxn) { // 查找m天之中可以拿的最多积分数
            maxn = c[i];
        }
    }
    printf("%lld\n", maxn); // 输出
    return 0; // 好习惯
}
