#include <stdio.h>
#include <stdbool.h>

#define MAXN 10005

long long a[MAXN];
bool used[MAXN];

int main() {
    long long n, c, i, j, minn, mi;
    scanf("%lld%lld", &n, &c);

    for (i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    long long l = 1, r = c,k=n;
    while (k != 0) {
        minn = 9999999999;
        for (i = l; i <= r; i++) {
            if (a[i] < minn && !used[i]) {
                minn = a[i];
                mi = i;
            }
        }

        if (k == 1) {
            printf("%lld\n", minn); // 当只剩最后一个数时换行
        } else {
            printf("%lld ", minn);
        }

        k--;
        used[mi] = true;

        long long z = 0;
        for (j = mi - 1; j >= 1; j--) {
            if (!used[j]) {
                l = j;
                z = 1;
                break;
            }
        }

        if (r < n) {
            r++; // 如果r还没到达数组末尾，则向右移动
        }

        if (z == 0) {
            l++; // 如果没有找到未使用的左侧元素，则l向右移动
        }
    }

    return 0;
}
