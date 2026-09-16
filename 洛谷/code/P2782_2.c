#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int north;
    int south;
} city;

city c[200005];
int lis[200005];
int ans = 0;

// 自定义的比较函数，用于qsort
int compare(const void *a, const void *b) {
    city *cityA = (city *)a;
    city *cityB = (city *)b;
    return cityA->north - cityB->north;
}

// 二分查找替换函数
void binary_search_replace(int *arr, int size, int value) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    if (left < size && arr[left] > value) {
        arr[left] = value;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &c[i].north, &c[i].south);
    }

    // 使用qsort对数组进行排序
    qsort(c, n, sizeof(city), compare);

    for (int i = 0; i < n; i++) {
        if (c[i].south > lis[ans - 1]) {
            lis[ans++] = c[i].south;
        } else {
            binary_search_replace(lis, ans, c[i].south);
        }
    }

    printf("%d\n", ans);
    return 0;
}
