// https://www.luogu.com.cn/problem/P9045
// 题意：一排 n 瓶橙汁品牌为 a_i，每次可花费 1 代价交换相邻两瓶。
// 求使最左边 k 瓶品牌两两不同的最小代价，无解输出 -1。
// 数据范围：1 <= k, a_i <= n <= 5*10^5。
// 算法标签：贪心
#include <stdio.h>
#include <stdbool.h> // 引入布尔类型支持

#define MAX_N 500001
bool book[MAX_N]; // 只需要两个数据就可以，开bool节省空间
long long ans;
int a, n, k, d;

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a);
        if (book[a] == 0) {
            book[a] = 1;
            ans += i - d - 1;
            d++;
        }
        if (d == k) { // 橙汁已经出现的品牌数已经满足了要求，直接输出代价并结束循环就可以了
            printf("%lld\n", ans);
            return 0;
        }
    }
    printf("-1\n"); // 如果没有找到k个不同的品牌，则输出-1
    return 0;
}
