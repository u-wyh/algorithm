// 用途：维护数组的区间加值与区间求和，展示序列分块的基本写法。
// 时间：建块 O(n)，单次操作 O(√n)。
// 空间：O(n)。
// 注意：n≤200000；下标从 1 开始，区间为闭区间；和值用 long long。
// 例题：https://www.luogu.com.cn/problem/P3372
// 题意：初始有 n 个数；操作 1 给 [l,r] 加 v，操作 2 输出 [l,r] 的和。
// 思路：整块只改懒标记与块和；两端不足整块的部分逐个修改或求和。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005, MAXB = 505;
long long value[MAXN], blockSum[MAXB], lazy[MAXB];
int blockSize, blockCount, blockId[MAXN], leftEnd[MAXB], rightEnd[MAXB];

void build(int n) {
    blockSize = max(1, (int)sqrt(n));
    blockCount = (n + blockSize - 1) / blockSize;
    for (int b = 1; b <= blockCount; ++b) {
        leftEnd[b] = (b - 1) * blockSize + 1;
        rightEnd[b] = min(n, b * blockSize);
        for (int i = leftEnd[b]; i <= rightEnd[b]; ++i) {
            blockId[i] = b;
            blockSum[b] += value[i];
        }
    }
}

void addPartial(int left, int right, long long delta) {
    int b = blockId[left];
    for (int i = left; i <= right; ++i) value[i] += delta;
    blockSum[b] += (right - left + 1LL) * delta;
}

void rangeAdd(int left, int right, long long delta) {
    int first = blockId[left], last = blockId[right];
    if (first == last) {
        addPartial(left, right, delta);
        return;
    }
    addPartial(left, rightEnd[first], delta);
    addPartial(leftEnd[last], right, delta);
    for (int b = first + 1; b < last; ++b) {
        lazy[b] += delta;
        blockSum[b] += (rightEnd[b] - leftEnd[b] + 1LL) * delta;
    }
}

long long sumPartial(int left, int right) {
    int b = blockId[left];
    long long answer = 0;
    for (int i = left; i <= right; ++i) answer += value[i] + lazy[b];
    return answer;
}

long long rangeSum(int left, int right) {
    int first = blockId[left], last = blockId[right];
    if (first == last) return sumPartial(left, right);
    long long answer = sumPartial(left, rightEnd[first]) +
                       sumPartial(leftEnd[last], right);
    for (int b = first + 1; b < last; ++b) answer += blockSum[b];
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> value[i];
    build(n);
    while (q--) {
        int op, left, right;
        cin >> op >> left >> right;
        if (op == 1) {
            long long delta;
            cin >> delta;
            rangeAdd(left, right, delta);
        } else {
            cout << rangeSum(left, right) << '\n';
        }
    }
    return 0;
}
