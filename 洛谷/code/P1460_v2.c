#include <stdio.h>
#include <stdbool.h> // 引入布尔类型支持

#define MAX_N 1000
#define MAX_M 1000

int ans[MAX_N]; // 存储解的数组
int a[MAX_N];   // 牛每天需要的每种维他命的最小量
int b[MAX_M][MAX_N]; // 每种饲料包含的各种维他命的量的多少
int c[MAX_N];  // 搜索过程中选择的饲料编号
int n, m, minn = 100000000;

// 判断是否满足维他命需求
bool pd(int x) {
    for (int i = 1; i <= n; i++) {
        int sum = 0;
        for (int j = 1; j <= x; j++) {
            sum += b[c[j]][i];
        }
        if (sum < a[i]) return false;
    }
    return true;
}

// 搜索函数
void search(int t, int s) {
    if (t > m) {
        if (pd(s)) {
            if (s < minn) {
                minn = s;
                for (int i = 1; i <= minn; i++) {
                    ans[i] = c[i];
                }
            }
        }
        return;
    }
    c[s + 1] = t;
    search(t + 1, s + 1);
    c[s + 1] = 0; // 注意：在C中，数组元素未初始化时其值是不确定的，但这里显式设为0是清晰的回溯操作
    search(t + 1, s);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &b[i][j]);
        }
    }
    search(1, 0);
    printf("%d ", minn);
    for (int i = 1; i <= minn; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}
