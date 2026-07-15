#include <stdio.h>
#include <stdlib.h>

#define N 10005

int T[N], D[N], n;


// 辅助比较函数，用于qsort
int compare_ints(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    scanf("%d", &n);
    int T_count = 0, D_count = 0;

    for (int i = 0; i < n; i++) {
        char s;
        int a;
        scanf(" %c %d", &s, &a); // 注意在%c前加空格以跳过任何之前的换行符
        if (s == 'T') {
            T[++T_count] = a;
        } else {
            D[++D_count] = a;
        }
    }

    qsort(T + 1, T_count, sizeof(int), (int (*)(const void*, const void*))compare_ints);
    qsort(D + 1, D_count, sizeof(int), (int (*)(const void*, const void*))compare_ints);

    double pos = 0, tim = 0, k = 1;
    int j = 1;

    for (int i = 1; i <= D_count; i++) {
        double temp = (T[j] - tim) * 1.0 / k + pos;
        while (temp <= D[i] && j <= T_count) {
            tim = T[j++];
            pos = temp;
            k++;
            temp = (T[j] - tim) * 1.0 / k + pos;
        }
        tim += (D[i] - pos) * 1.0 / (1.0 / k);
        pos = D[i];
        k++;
    }

    double temp = (T[j] - tim) * 1.0 / k + pos;
    while (temp <= 1000 && j <= T_count) {
        tim = T[j++];
        pos = temp;
        k++;
        temp = (T[j] - tim) * 1.0 / k + pos;
    }

    if (pos < 1000) {
        tim += (1000 - pos) * k;
    }

    printf("%d", (int)(tim + 0.5));

    return 0;
}
