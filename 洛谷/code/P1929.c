#include<stdio.h>
#include<string.h>
#define Min(x,y) ((x)<(y)?(x):(y))
#define N  206

int a[N], n, f[N];

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    memset(f, 0x3f, sizeof(f));
    int oo = f[0];  // 使用f[0]来表示一个很大的数，表示不可达
    f[1] = 0;  // 初始状态，到达第一个位置不需要任何操作

    for(int i = 2; i <= n; i++) {
        if(a[i] <= a[i-1] + 1) {
            f[i] = f[i-1] + 1;  // 直接在前一个位置的基础上加1
        }
        for(int j = i - 1; j > 0; j--) {
            for(int k = j - 1; k > 0; k--) {
                if(((1 << (j - k)) + a[k]) >= a[i]) {
                    f[i] = Min(f[i], f[j] + j - k + 1);
                }
            }
        }
    }

    // 如果f[n]仍然是初始化的最大值，表示无法到达，输出-1；否则输出f[n]
    printf("%d\n", f[n] >= oo ? -1 : f[n]);

    return 0;
}
