#include <stdio.h>
#include <stdlib.h>

#define int long long
#define N 1000000 + 100000

// 比较函数，用于qsort
int compare(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (y - x); // 注意这里返回y-x以实现降序排序
}

int main() {
    int n, m, k;
    scanf("%lld %lld %lld", &n, &m, &k);
    int a[N], b[N];
    int ans = 0, kk = 0;

    // 读取数组a并求和
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
        ans += a[i];
    }

    // 读取数组b并求和
    for (int i = 0; i < m; i++) {
        scanf("%lld", &b[i]);
        ans += b[i];
    }

    // 对数组a进行排序（降序）
    qsort(a, n, sizeof(int), compare);

    // 找出满足条件的元素数量并更新ans
    int minn = (n < m) ? n : m;
    for (int i = 0; i < minn; i++) {
        if (a[i] > k) {
            ans += a[i];
            kk++;
        }
    }

    // 剩下的元素都按k计算
    ans += k * (minn - kk);

    // 输出结果
    printf("%lld\n", ans);

    // main函数应返回int类型，并且通常返回0表示成功
    return 0;
}
