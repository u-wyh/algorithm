// 用途：求长度为 k 的每个连续窗口的最小值和最大值。
// 时间：O(n)。
// 空间：O(n)。
// 注意：1≤k≤n≤10^6；队列保存下标，先移除窗口外下标。
// 例题：https://www.luogu.com.cn/problem/P1886
// 题意：窗口从左到右每次移动一格，依次输出全部窗口最小值、最大值。
// 思路：队首是当前答案；插入新下标前，从队尾删掉不可能再成为答案的下标。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
int value[MAXN], que[MAXN];

void printWindows(int n, int k, bool wantMinimum) {
    int head = 0, tail = 0;
    bool first = true;
    for (int i = 1; i <= n; ++i) {
        while (head < tail && que[head] <= i - k) ++head;
        while (head < tail && (wantMinimum ? value[que[tail - 1]] >= value[i]
                                          : value[que[tail - 1]] <= value[i]))
            --tail;
        que[tail++] = i;
        if (i >= k) {
            if (!first) cout << ' ';
            first = false;
            cout << value[que[head]];
        }
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> value[i];
    printWindows(n, k, true);
    printWindows(n, k, false);
    return 0;
}
