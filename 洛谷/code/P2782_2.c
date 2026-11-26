// https://www.luogu.com.cn/problem/P2782
// 题意：输入城市对数 N，以及 N 行每行两个整数，分别表示南岸和北岸一对友好城市的坐标。
// 河的南北两岸各有 N 个位置不同的城市，北岸每个城市唯一对应南岸一个友好城市，每对申请修一条直线航道。
// 要求选出尽量多的航道申请予以批准，使得任意两条被批准的航道都不相交。
// 输出一个整数，表示政府所能批准的最多申请数量。
// 数据范围：对于 100% 的数据，1 <= N <= 2*10^5，0 <= x_i <= 10^6。
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
