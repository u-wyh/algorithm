#include <stdio.h>
#include <stdlib.h>

void selectionSort(int arr[], int n) {
    int i, j, minIndex, temp;
    for (i = 0; i < n - 1; i++) {
        minIndex = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] > arr[minIndex]) {
                minIndex = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int **a = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        a[i] = (int *)malloc(n * sizeof(int));
    }

    int *sum = (int *)malloc(n * n * sizeof(int));
    int aa = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == 0) {
                int rowSum = 0, colSum = 0;
                for (int k = 0; k < n; k++) {
                    rowSum += a[i][k];
                    colSum += a[k][j];
                }
                sum[aa++] = rowSum + colSum - a[i][j]; // 减去自身分数，因为不能在自己位置
            }
        }
    }

    selectionSort(sum, aa);

    if (aa > 0) {
        printf("%d\n", sum[0]);
    } else {
        printf("Bad Game!\n");
    }

    // 释放内存
    for (int i = 0; i < n; i++) {
        free(a[i]);
    }
    free(a);
    free(sum);

    return 0;
}
