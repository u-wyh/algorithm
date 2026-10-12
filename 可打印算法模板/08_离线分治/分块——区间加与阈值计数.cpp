// 用途：区间加值后，查询区间里有多少个数不小于给定阈值。
// 时间：建块 O(n log n)，单次操作 O(√n log n)。
// 空间：O(n)。
// 注意：n≤10^6；基础值与懒标记用 long long，区间为闭区间。
// 例题：https://www.luogu.com.cn/problem/P2801
// 题意：M l r v 给 [l,r] 加 v；A l r v 询问其中 ≥v 的元素个数。
// 思路：每块保存未加懒标记的有序副本；整块查询二分，边角直接枚举。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005, MAXB = 1005;
long long value[MAXN], sortedValue[MAXN], lazy[MAXB];
int blockSize, blockCount, blockId[MAXN], leftEnd[MAXB], rightEnd[MAXB];

void rebuild(int block) {
    for (int i = leftEnd[block]; i <= rightEnd[block]; ++i)
        sortedValue[i] = value[i];
    sort(sortedValue + leftEnd[block], sortedValue + rightEnd[block] + 1);
}

void build(int n) {
    blockSize = max(1, (int)sqrt(n));
    blockCount = (n + blockSize - 1) / blockSize;
    for (int block = 1; block <= blockCount; ++block) {
        leftEnd[block] = (block - 1) * blockSize + 1;
        rightEnd[block] = min(n, block * blockSize);
        for (int i = leftEnd[block]; i <= rightEnd[block]; ++i)
            blockId[i] = block;
        rebuild(block);
    }
}

void addPartial(int left, int right, long long delta) {
    int block = blockId[left];
    for (int i = left; i <= right; ++i) value[i] += delta;
    rebuild(block);
}

void rangeAdd(int left, int right, long long delta) {
    int first = blockId[left], last = blockId[right];
    if (first == last) {
        addPartial(left, right, delta);
        return;
    }
    addPartial(left, rightEnd[first], delta);
    addPartial(leftEnd[last], right, delta);
    for (int block = first + 1; block < last; ++block)
        lazy[block] += delta;
}

int countPartial(int left, int right, long long threshold) {
    int block = blockId[left], answer = 0;
    for (int i = left; i <= right; ++i)
        answer += value[i] + lazy[block] >= threshold;
    return answer;
}

int countWhole(int block, long long threshold) {
    auto begin = sortedValue + leftEnd[block];
    auto end = sortedValue + rightEnd[block] + 1;
    return end - lower_bound(begin, end, threshold - lazy[block]);
}

int rangeCount(int left, int right, long long threshold) {
    int first = blockId[left], last = blockId[right];
    if (first == last) return countPartial(left, right, threshold);
    int answer = countPartial(left, rightEnd[first], threshold) +
                 countPartial(leftEnd[last], right, threshold);
    for (int block = first + 1; block < last; ++block)
        answer += countWhole(block, threshold);
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
        char op;
        int left, right;
        long long x;
        cin >> op >> left >> right >> x;
        if (op == 'M') rangeAdd(left, right, x);
        else cout << rangeCount(left, right, x) << '\n';
    }
    return 0;
}
