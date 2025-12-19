#include <stdio.h>
#include <limits.h> // 引入INT_MAX

#define MAX_N 100001

int a[MAX_N], b[MAX_N], map[MAX_N], f[MAX_N];

int main() {
    int n;
    scanf("%d", &n);

    // 初始化map和f数组
    for (int i = 0; i < MAX_N; i++) {
        map[i] = 0; // 通常初始化为0或特定值，根据实际需求
        f[i] = INT_MAX; // 初始化f数组为最大整数
    }

    // 读取a数组并填充map
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        map[a[i]] = i;
    }

    // 读取b数组
    for (int i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
    }

    int len = 0;
    f[0] = 0; // 初始化f[0]为0

    for (int i = 1; i <= n; i++) {
        int l = 0, r = len, mid;

        // 如果当前b[i]的映射值大于f[len]，则直接添加到f数组末尾
        if (map[b[i]] > f[len]) {
            f[++len] = map[b[i]];
        } else {
            // 二分查找合适的插入位置
            while (l < r) {
                mid = (l + r) / 2;
                if (f[mid] > map[b[i]]) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
            // 更新f[l]为较小值
            f[l] = (map[b[i]] < f[l]) ? map[b[i]] : f[l];
        }
    }

    printf("%d\n", len);
    return 0;
}
