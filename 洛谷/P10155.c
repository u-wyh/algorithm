#include <stdio.h>

#define NN 2000004 // 定义数组大小

int a[NN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    if (a[n] != n) {
        printf("-1\n");
        return 0;
    }
    int minn = 1e9, ans = 0;
    for (int i = n; i >= 1; i--) {
        if (a[i] < minn) {
            minn = a[i];
        } else {
            ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}
