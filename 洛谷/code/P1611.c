#include <stdio.h>

long long ans;
int p[7] = {1, 10, 100, 1000, 10000, 100000, 1000000};

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    int s = 0, v = a;
    while (v) {
        v /= 10;
        s++; // 计算位数
    }

    for (int i = a; i < b; i++) { // 枚举n
        int n = i;
        int m = (n % 10) * p[s - 1] + n / 10; // 如上文计算m
        while (n != m) { // 若n == m，则m枚举完毕
            if (n < m && m <= b) { // 即符合条件，ans++
                ans++;
            }
            m = (m % 10) * p[s - 1] + m / 10; // 枚举m
        }
    }

    printf("%lld\n", ans);
    return 0;
}
