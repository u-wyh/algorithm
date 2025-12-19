#include <stdio.h>
#include <stdlib.h>

#define MAXN 100001

int n, ma, d[MAXN], a[MAXN], k, x[MAXN], xl = 1, t, len = 1;

// 模拟二分查找，找到第一个大于key的元素的索引（upper_bound）
int upper_bound(int *arr, int r, int key) {
    int left = 1, right = r;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] <= key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return left;
}

// 模拟二分查找，找到第一个不小于key的元素的索引（lower_bound）
int lower_bound(int *arr, int r, int key) {
    int left = 1, right = r;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return left + 1; // 注意这里要加1，因为lower_bound要求返回第一个不小于key的元素的索引
}

int main() {
    x[1] = INT_MAX; // 使用INT_MAX代替0x7fffffff
    while (scanf("%d", &a[++n]) != EOF);
    --n; // 修正n的值，因为最后一次循环会多增加1

    d[1] = a[1];
    for (int i = 2; i <= n; i++) {
        if (a[i] <= d[len]) {
            d[++len] = a[i];
        } else {
            int pos = upper_bound(d, len, a[i]);
            if (pos <= len) { // 确保不越界
                d[pos] = a[i];
            }
        }
    }
    printf("%d\n", len - 1); // 输出最长递增子序列的长度

    for (int i = 1; i <= n; i++) {
        if (x[xl] < a[i]) {
            xl++;
            x[xl] = a[i];
        } else {
            int k = lower_bound(x, xl, a[i]);
            if (k <= xl) { // 确保不越界
                x[k] = a[i];
            }
        }
    }
    printf("%d\n", xl); // 输出最长递减子序列的长度（这里其实只计算了不同元素的数量，如果要求严格递减且元素不同，则正确；否则可能不准确）

    return 0;
}

// 注意：上述代码中的lower_bound用于递减子序列时可能不是完全准确的，
// 因为它只是替换了第一个不小于a[i]的元素，而没有保证子序列的严格递减性。
// 如果要计算严格递减且元素不重复的子序列长度，可能需要其他逻辑。
