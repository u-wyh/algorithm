#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, i, sum = 1;
    scanf("%d", &n);
    int a[n];
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    qsort(a, n, sizeof(int), compare);
    for (i = 0; i < n; i++) {
        if (a[i] < sum) {
            continue;
        } else {
            sum++;
        }
    }
    printf("%d\n", sum-1);

    return 0;
}
