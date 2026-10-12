// 用途：线性构建下标为中序、数值为小根堆的笛卡尔树。
// 时间：建树 O(n)。
// 空间：O(n)。
// 注意：相等值按原代码规则处理；n<=1e7，内存占用较大。
// 例题：https://www.luogu.com.cn/problem/P5854
// 题意：给定数组，建中序顺序与下标一致、满足小根堆性质的二叉树。
// 思路：维护递增单调栈，新值弹出较大节点并调整左右孩子。
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10000001;

int arr[MAXN];
int ls[MAXN];
int rs[MAXN];
int sta[MAXN];
int n;

// 单调栈维护尚未确定右儿子的节点。
void build() {
    int top = 0;
    for (int i = 1; i <= n; i++) {
        int pos = top;

        while (pos > 0 && arr[sta[pos]] > arr[i]) {
            pos--;
        }

        if (pos > 0) {
            rs[sta[pos]] = i;
        }

        if (pos < top) {
            ls[i] = sta[pos + 1];
        }

        sta[++pos] = i;//加入栈中
        top = pos;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    build();
    long long ans1 = 0, ans2 = 0;
    for (int i = 1; i <= n; i++) {
        ans1 ^= 1LL * i * (ls[i] + 1);
        ans2 ^= 1LL * i * (rs[i] + 1);
    }
    cout << ans1 << " " << ans2 << endl;
    return 0;
}
