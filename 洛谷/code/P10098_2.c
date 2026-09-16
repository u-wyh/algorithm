#include <stdio.h>
#include <stdlib.h>

#define N 105

typedef struct {
    long long z, a, b;
} node;

node mp[N];
int n;
long long p;

int judge(long long x) { // 二分查找的辅助函数
    long long sum = 0;
    for (int i = 0; i < n; i++) { // 注意数组索引从0开始
        if (x <= mp[i].z) {
            sum += mp[i].a * x;
        } else {
            sum += (mp[i].a * mp[i].z + mp[i].b * (x - mp[i].z));
        }
    }
    return sum >= p; // 比较
}

int main() {
    scanf("%d %lld", &n, &p); // 使用scanf进行输入
    for (int i = 0; i < n; i++) { // 注意数组索引从0开始
        scanf("%lld %lld %lld", &mp[i].z, &mp[i].a, &mp[i].b);
    }

    long long l = 1, r = p, mid, ans = 0; // 开 long long
    while (l <= r) {
        mid = (l + r) / 2; // 注意这里使用整数除法
        if (judge(mid)) {
            r = mid - 1;
            ans = mid;
        } else {
            l = mid + 1;
        }
    }

    printf("%lld\n", ans); // 使用printf进行输出
    return 0;
}
