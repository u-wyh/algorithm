#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef long long ll;

// 鱼的结构体
typedef struct {
    ll big;
    ll id;
} fish;

// 比较函数，用于qsort
int fishCmp(const void *a, const void *b) {
    fish *fa = (fish *)a;
    fish *fb = (fish *)b;
    return fa->big - fb->big;
}

// 判断一条鱼是否可以留下来
bool solve(fish *a, ll n, ll x) {
    ll temp = a[x].big;
    for (ll i = 0; i < n; i++) {
        if (i == x) continue;
        if (temp > a[i].big) {
            temp += a[i].big;
        } else {
            return false;
        }
    }
    return true;
}

int main() {
    ll n;
    scanf("%lld", &n);
    fish a[500005];
    for (ll i = 0; i < n; i++) {
        scanf("%lld", &a[i].big);
        a[i].id = i + 1; // 题目要求输出从1开始的id
    }

    // 使用qsort进行排序
    qsort(a, n, sizeof(fish), fishCmp);

    ll l = 0, r = n - 1;
    ll res = n; // 初始化为n，表示没有找到符合条件的鱼
    while (l <= r) {
        ll mid = (l + r) / 2;
        if (solve(a, n, mid)) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    // 如果res仍然是n，则表示没有鱼可以留下来
    bool arr[500005] = {0};
    if (res != n) {
        for (ll i = res; i < n; i++) {
            arr[a[i].id - 1] = true; // 数组索引从0开始，但id从1开始
        }
    }

    // 输出结果
    for (ll i = 0; i < n; i++) {
        putchar(arr[i] ? 'T' : 'N');
    }
    putchar('\n'); // 加上换行符，使输出更规范

    return 0;
}
