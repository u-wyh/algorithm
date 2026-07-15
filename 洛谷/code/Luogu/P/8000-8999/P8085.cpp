// https://www.luogu.com.cn/problem/P8085
//这道题哈希完全就是工具人的作用
//首先处理出每个位置上的字符串到左边相同的字符距离是多少
//也要记录自己右边相同字符的位置
//然后对第一个维护一个窗口  只要最左边的字符弹出 那么将自己右边的那个设置为-1
//然后对窗口哈希调整
#include <bits/stdc++.h>
using namespace std;
const int INF = 2147483647;
const int MAXN = 1e6 + 3;
const int BASE = 13131;

int L1[MAXN], R1[MAXN];
int L2[MAXN], R2[MAXN];
int A[MAXN], B[MAXN], n, m;
long long H[MAXN], P[MAXN];
map<string, int> M;

int main() {
    string t;

    while (cin >> t && t != "$") {
        R1[M[t]] = ++n;//表示这个词语右边最早再次出现的位置
        L1[n] = M[t];//表示这个词语左边最早再次出现的位置
        M[t] = n;
    }

    M.clear();

    while (cin >> t && t != "$") {
        R2[M[t]] = ++m;
        L2[m] = M[t];
        M[t] = m;
    }

    for (int i = 1; i <= n; ++i) if (!R1[i]) R1[i] = INF;
    for (int i = 1; i <= m; ++i) if (!R2[i]) R2[i] = INF;//如果右边没有出现过

    for (int i = 1; i <= n; ++i) A[i] = (L1[i] ? i - L1[i] : -1);
    for (int i = 1; i <= m; ++i) B[i] = (L2[i] ? i - L2[i] : -1);//该位置的单词距离自己左边出现最早位置的距离

    long long h0 = 0, h = 0;
    P[0] = 1;
    for (int i = 1; i <= m; ++i) P[i] = P[i - 1] * BASE;

    for (int i = 1; i <= m; ++i) h0 = h0 * BASE + B[i];//h0是我们所要求的
    for (int i = 1; i <= m; ++i) h = h * BASE + A[i];

    if (h == h0) {
        cout << 1 << endl;
        return 0;
    }

    for (int i = m + 1; i <= n; ++i) {
        h = h * BASE + A[i] - A[i - m] * P[m];//还没有完全修正前的哈希值

        if (R1[i - m] <= i) {//即引发的变化在如今查询的范围中
            int overlapIndex = R1[i - m];
            h -= A[overlapIndex] * P[i - overlapIndex];//减去错误的哈希值
            A[overlapIndex] = -1;
            h += A[overlapIndex] * P[i - overlapIndex];  // 加上修正后的哈希值
        } else if (R1[i - m] <= n) {
            A[R1[i - m]] = -1;
        }

        if (h == h0) {
            cout << i - m + 1 << endl;
            return 0;
        }
    }

    return 0;
}
