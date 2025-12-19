#include <stdio.h>
#include <math.h>

#define INF 0x7fffffff

int n, ans = INF;

// 声明深度优先搜索函数
void dfs(int dep, int num);

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= (int)sqrt(n); i++) {
        // 因数一定是成对出现，所以我们枚举的a实际上是i和n/i
        if (n % i == 0) {
            if (n / i != i) dfs(0, i);  // n/(n/i)=i
            if (i != 1 && i != n) dfs(0, n / i);  // 避免重复和n本身的情况
        }
    }
    if (ans != INF) printf("%d\n", ans);  // 判断能否到达
    else printf("-1\n");
    return 0;
}

// 定义深度优先搜索函数
void dfs(int dep, int num) {
    if (num == 0) {
        // 边界条件
        if (dep < ans) ans = dep;  // 更新最小深度
        return;
    }
    num--;  // 把式子里面的1减掉
    for (int i = 2; i <= 9; i++) {  // 枚举k
        if (num % i == 0) {  // 判断整除
            dfs(dep + 1, num / i);
        }
    }
}
