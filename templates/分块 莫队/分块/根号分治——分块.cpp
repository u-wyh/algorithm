// 初始化，C++版
// 给定一个长度为n的数组arr，接下来有m条操作，操作格式如下
// 操作 1 x y z : 从arr[y]开始，下标每次+x，所有相应位置的数都+z，题目保证 y <= x
// 操作 2 x y   : 打印arr[x..y]的累加和，答案对1000000007取余
// 1 <= n、m <= 2 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P5309
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 这道题的思路真的是特别的巧妙
// 对于x大于blen的  直接暴力添加即可
// 对于x小于等于blen的 我们可以发现 题目中明确的说了y<=x
// 并且这个加操作是对整体进行一个加操作  那么我们可以将这样的加操作换个视角来看
// 我们认为这是将整体按照长度为x做一个周期  统计这个周期的加成前缀和  和  加成后缀和
// 加成前缀和 表示的是 从1到i  的加成前缀和  
// 加成后缀和 表示的是 从i到x  的加成后缀和
// 对于相同的x  所有的周期的这个值是一样的
// 在统计答案的时候  我们首先求出那些长度大于blen的贡献
// 对于小于blen的  可以通过这个周期来计算  两个散块加上中间的整块  整块都是一样的  相当于是将周期作为块的编号
// 其实对于每个周期而言  最后一个周期可能是不完整的  但是对答案其实是没有影响的 因为本来就不可能统计这个位置的答案（因为不存在）
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200001;
const int MAXB = 501;
const int MOD  = 1000000007;

int n, m;

// 这里的pre  suf数组相当于是每个块的加成效果的前缀和  和   后缀和
long long pre[MAXB][MAXB];
long long suf[MAXB][MAXB];
long long arr[MAXN];
long long sum[MAXB];

int blen, bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

void add(int x, int y, long long z) {
    if (x <= blen) {
        for (int i = y; i <= x; i++) {
            pre[x][i] += z;
        }
        for (int i = y; i >= 1; i--) {
            suf[x][i] += z;
        }
    } else {
        for (int i = y; i <= n; i += x) {
            arr[i] += z;
            sum[bi[i]] += z;
        }
    }
}

long long querySum(int l, int r) {
    int lb = bi[l], rb = bi[r];
    long long ans = 0;
    if (lb == rb) {
        for (int i = l; i <= r; i++) {
            ans += arr[i];
        }
    } else {
        for (int i = l; i <= br[lb]; i++) {
            ans += arr[i];
        }
        for (int i = bl[rb]; i <= r; i++) {
            ans += arr[i];
        }
        for (int b = lb + 1; b <= rb - 1; b++) {
            ans += sum[b];
        }
    }
    return ans;
}

long long query(int l, int r) {
    long long ans = querySum(l, r);
    for (int x = 1, lth, rth, num; x <= blen; x++) {
        lth = (l - 1) / x + 1;
        rth = (r - 1) / x + 1;
        num = rth - lth - 1;
        if (lth == rth) {
            ans = ans + pre[x][(r - 1) % x + 1] - pre[x][(l - 1) % x];
        } else {
            ans = ans + suf[x][(l - 1) % x + 1] + pre[x][x] * num + pre[x][(r - 1) % x + 1];
        }
    }
    return ans % MOD;
}

void prepare() {
    blen = (int)sqrt(n);
    bnum = (n + blen - 1) / blen;
    for (int i = 1; i <= n; i++) {
        bi[i] = (i - 1) / blen + 1;
    }
    for (int b = 1; b <= bnum; b++) {
        bl[b] = (b - 1) * blen + 1;
        br[b] = min(b * blen, n);
        for (int i = bl[b]; i <= br[b]; i++) {
            sum[b] += arr[i];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    prepare();
    for (int i = 1, op, x, y, z; i <= m; i++) {
        cin >> op >> x >> y;
        if (op == 1) {
            cin >> z;
            add(x, y, z);
        } else {
            cout << query(x, y) << '\n';
        }
    }
    return 0;
}