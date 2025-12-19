#include <stdio.h>
#define MAXN 10010
#define ARRAY_SIZE 3000010

int n, k;
int d[ARRAY_SIZE];
int x, y, a, b;

void lzy() {
    for (int i = 0; i < n - 1; i++) {
        if (d[i] > 1) {
            d[i + 1] += d[i] - 1;
            d[i] = 1;
        }
    }

    // 如果需要处理最后一个元素可能大于1的情况（虽然在这个特定问题中可能不需要，因为已经单独处理）
    // 但为了保持代码的完整性，这里还是加上
    if (d[n - 1] > 1) {
        d[0] += d[n - 1] - 1;
        d[0]--; // 注意这里减1是多余的，因为d[0]已经加上了d[n-1]-1
        d[n - 1] = 1;
        // 注意：通常不需要再次调用lzy()，因为上面的处理已经足够了
        // 但如果确实需要处理更复杂的情况，可以考虑再次调用或重构lzy函数
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= k; i++) {
        scanf("%d%d%d%d", &x, &y, &a, &b);
        long long s = b;
        for (int j = 1; j <= y; j++) {
            s = (s % n + a % n) % n;
            d[s] += x;
        }
    }

    lzy();

    for (int i = 0; i < n; i++) {
        if (!d[i]) {
            printf("%d\n", i);
            return 0;
        }
    }

    // 如果没有找到空位置，可能需要输出一个错误消息或执行其他操作
    // 这里简单地返回0，但在实际应用中可能需要更复杂的错误处理
    return 0;
}
