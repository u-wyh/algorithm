// https://www.luogu.com.cn/problem/P3503
// 题意：输入木块堆数 n（1..n 排成一行）、询问数 m，各堆初始木块数 a_1..a_n，以及 m 个参数 k_1..k_m。
// 每次操作只能从当前高度严格大于 k 的堆顶拿走 1 块放到相邻堆上（不能新建堆）；求调整后所有高度 >= k 的最长连续子段最大长度。
// 输出一行 m 个整数，依次表示对应参数 k_j 下的最长连续子段长度。
// 数据范围：1 <= n <= 10^6，1 <= m <= 50，1 <= a_i, k_j <= 10^9。
#include <iostream>
#include <cstdio>
#include <algorithm>
// 算法标签：前缀和、单调栈
using namespace std;
const int MAXN = 1e6 + 5;

int n, m;
int a[MAXN];
long long s[MAXN];
int stk[MAXN]; // 单调栈存储下标

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    while (m--) {
        int k;
        scanf("%d", &k);
        // 计算前缀和: s[i] = Σ(a[j]-k) for j=1 to i
        s[0] = 0;
        for (int i = 1; i <= n; i++) {
            s[i] = s[i - 1] + a[i] - k;
        }

        // 构建单调栈（存储前缀和递减的下标）
        int top = 0;
        stk[++top] = 0; // 压入起点0
        for (int i = 1; i <= n; i++) {
            if (s[i] < s[stk[top]]) {
                stk[++top] = i;
            }
        }

        int ans = 0;
        // 倒序遍历前缀和
        for (int i = n; i >= 0; i--) {
            // 若i在栈顶则弹出（避免自比较）
            if (i == stk[top]) {
                top--;
                if (top == 0) break;
            }
            // 弹出栈顶直到栈中元素满足条件
            while (top > 1 && s[i] >= s[stk[top - 1]]) {
                top--;
            }
            // 更新最大长度
            if (s[i] >= s[stk[top]]) {
                ans = max(ans, i - stk[top]);
            }
        }
        printf("%d ", ans);
    }
    return 0;
}