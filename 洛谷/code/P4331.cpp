// 数字序列，C++版
// 给定一个长度为n的数组A，要求构造出一个长度为n的递增数组B
// 希望 |A[1] - B[1]| + |A[2] - B[2]| + ... + |A[n] - B[n]| 最小
// 打印这个最小值，然后打印数组B，如果有多个方案，只打印其中的一个
// 1 <= n <= 10^6
// 0 <= A[i] <= 2^32 - 1
// 测试链接 : https://www.luogu.com.cn/problem/P4331
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 这道题的操作实际上就是要求将数组分片  每片上的数字要是递增的  并且和原来数组之差的绝对值之和最小
// 我们可以想到 如果想要这个和最小 那么数字应该要变成中位数
// 这道题很巧妙的使用了单调栈来实现  借助左偏树寻找中位数
// 单调栈要求大压小 相等可以压相等  每个单调栈中的点都是一个集合  它们的代表值（也就是中位数）就是他们所对应的片值
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000001;

int n;
long long arr[MAXN];

// 左偏树需要
int ls[MAXN];
int rs[MAXN];
int dist[MAXN];

// 并查集向上的路径
int fa[MAXN];
// 集合表达区域的左下标
int from[MAXN];
// 集合表达区域的右下标
int to[MAXN];
// 集合里有几个数字  这里是真实的数字个数  就是在堆中真实存在的数字
int siz[MAXN];
// 单调栈
int stk[MAXN];
// 构造的数组
long long ans[MAXN];

void prepare() {
    dist[0] = -1;
    for (int i = 1; i <= n; i++) {
        ls[i] = rs[i] = dist[i] = 0;
        fa[i] = from[i] = to[i] = i;
        siz[i] = 1;
    }
}

int find(int i) {
    fa[i] = fa[i] == i ? i : find(fa[i]);
    return fa[i];
}

int merge(int i, int j) {
    if (i == 0 || j == 0) {
        return i + j;
    }
    int tmp;
    // 维护大根堆
    if (arr[i] < arr[j]) {
        tmp = i; i = j; j = tmp;
    }
    rs[i] = merge(rs[i], j);
    if (dist[ls[i]] < dist[rs[i]]) {
        tmp = ls[i]; ls[i] = rs[i]; rs[i] = tmp;
    }
    dist[i] = dist[rs[i]] + 1;
    fa[ls[i]] = fa[rs[i]] = i;
    return i;
}

int pop(int i) {
    fa[ls[i]] = ls[i];
    fa[rs[i]] = rs[i];
    fa[i] = merge(ls[i], rs[i]);
    ls[i] = rs[i] = dist[i] = 0;
    return fa[i];
}

long long compute() {
    int stackSize = 0;
    for (int i = 1, pre, cur, s; i <= n; i++) {
        while (stackSize > 0) {
            pre = find(stk[stackSize]);
            cur = find(i);
            if (arr[pre] <= arr[cur]) {
                break;
            }
            s = siz[pre] + siz[cur];
            cur = merge(pre, cur);
            // 大根堆只保留到上中位数
            while (s > ((i - from[pre] + 1 + 1) / 2)) {
                // 堆里面的数字个数只有真实个数的一半  这样可以很快的求出中位数
                cur = pop(cur);
                s--;
            }
            from[cur] = from[pre];
            to[cur] = i;
            siz[cur] = s;
            stackSize--;
        }
        stk[++stackSize] = i;
    }
    long long sum = 0;
    for (int i = 1, cur; i <= stackSize; i++) {
        cur = find(stk[i]);
        for (int j = from[cur]; j <= to[cur]; j++) {
            ans[j] = arr[cur];
            sum += llabs(ans[j] - arr[j]);
        }
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    prepare();
    long long x;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        arr[i] = x - i;
    }
    long long res = compute();
    cout << res << "\n";
    for (int i = 1; i <= n; i++) {
        cout << ans[i] + i << (i == n ? '\n' : ' ');
    }
    return 0;
}