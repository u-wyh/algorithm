#include <stdio.h>
#include <stdlib.h>

#define Max 10000

int tian[Max], king[Max];
int n, i, j, ii, jj, ans;

// 比较函数，用于qsort
int cmp(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &tian[i]);
    }
    for (i = 1; i <= n; i++) {
        scanf("%d", &king[i]);
    }

    // 使用qsort进行排序
    qsort(tian + 1, n, sizeof(int), cmp);
    qsort(king + 1, n, sizeof(int), cmp);

    ans = 0;
    ii = n;
    jj = n;

    for (i = 1, j = 1; i <= ii;) {
        if (tian[i] > king[j]) {
            ans += 200;
            i++;
            j++;
        } else if (tian[i] < king[j]) {
            ans -= 200;
            j++;
            ii--;
        } else {
            if (tian[ii] > king[jj]) {
                ans += 200;
                ii--;
                jj--;
            } else {
                if (tian[ii] < king[j]) {
                    ans -= 200;
                }
                ii--;
                j++;
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}
