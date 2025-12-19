#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define ll long long
#define INF INT_MAX

// 自定义的read函数，用于读取整数
int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch > '9' || ch < '0') {
        if (ch == '-') f = -f;
        ch = getchar();
    }
    while (ch <= '9' && ch >= '0') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int n, cnt, ans, a[100005], q[100005], sum[100005];

// 自定义的比较函数，用于qsort
int mysort(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// 二分查找函数
int search(int k) {
    int l = 1, r = cnt, mid;
    while (l <= r) {
        mid = (l + r) / 2;
        if (q[mid] == k) return mid;
        if (q[mid] < k) l = mid + 1;
        if (q[mid] > k) r = mid - 1;
    }
    return 0;
}

int main() {
    n = read();
    for (int i = 0; i < n; i++) {
        a[i] = read();
    }
    qsort(a, n, sizeof(int), mysort);

    for (int i = 0; i < n; i++) {
        int k = search(a[i] - 1);
        if (!k) {
            q[++cnt] = a[i];
            sum[cnt] = 1;
            continue;
        }
        while (q[k + 1] == q[k] && k < cnt) k++;
        q[k]++;
        sum[k]++;

        // 调整sum和q数组以保持它们之间的顺序
        while (sum[k] < sum[k + 1] && k < cnt) {
            int tmp_q = q[k];
            q[k] = q[k + 1];
            q[k + 1] = tmp_q;
            int tmp_sum = sum[k];
            sum[k] = sum[k + 1];
            sum[k + 1] = tmp_sum;
            k++;
        }
    }

    ans = INF;
    for (int i = 1; i <= cnt; i++) {
        ans = (ans < sum[i]) ? ans : sum[i];
    }
    printf("%d\n", ans);
    return 0;
}
