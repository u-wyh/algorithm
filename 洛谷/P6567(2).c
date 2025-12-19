#include <stdio.h>
#include <string.h>

#define MAX_N 500005

int n, m;
int f[MAX_N];

typedef struct {
    int k, a;
} node;

node e[205];

int cmp(const void *a, const void *b) {
    node *na = (node *)a;
    node *nb = (node *)b;
    return nb->k - na->k; // 降序排序
}

void bubbleSort(node arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j].k < arr[j+1].k) {
                // 交换 arr[j] 和 arr[j+1]
                node temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    // freopen("watch.in", "r", stdin);
    // freopen("watch.out", "w", stdout);
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &e[i].k, &e[i].a);
    }
    // 使用qsort代替冒泡排序
    qsort(e, n, sizeof(node), cmp);

    memset(f, 0, sizeof(f));
    f[0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < MAX_N; j++) {
            if (j >= e[i].k && f[j - e[i].k] && f[j - e[i].k] <= e[i].a) {
                f[j] = f[j - e[i].k] + 1;
            }
            // 注意：在C中，我们不需要“清空”f[j]，因为memset已经在开始时清零了
            // 而且C的数组不会自动初始化为0，需要手动memset或使用其他方式
        }
    }

    for (int i = 0; i < m; i++) {
        int x;
        scanf("%d", &x);
        if (f[x]) printf("Yes\n");
        else printf("No\n");
    }

    return 0;
}
