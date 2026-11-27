// https://www.luogu.com.cn/problem/P7871
// 题意：n 块石块排成一列（编号 1..n），为每块赋互不相同的正整数能级 A_1..A_n。
// 若第 i 块处于激发态，当其两侧均有相邻块时将能量传给第 i-1 与第 i+1 块中能级较小的一块；
// 若仅有单侧相邻块则传给该侧相邻块（即使 i 的能级更低也可传播）。
// 给定 q 个条件 (s_i, t_i)，要求激活第 s_i 块后能量最终经过第 t_i 块。
// 若存在合法赋值方案，输出字典序最小的序列 A；
// 否则输出 QED。
// 第一行输入 n, q，接下来 q 行每行 s_i, t_i。
// 数据范围：3 <= n <= 3*10^5，0 <= q <= 3*10^5，1 <= s_i, t_i <= n；
// 注：题面未明确标注输出能级 A_i 的数值上界（仅要求为互不相同的正整数）。
// 算法标签：差分、贪心、构造
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>

using namespace std;

typedef long long i64;
const int INF = INT_MAX;
const int MAXN = 1e5 + 3;

int read() {
    int w = 1, c, ret = 0;
    while ((c = getchar()) > '9' || c < '0') w = (c == '-' ? -1 : 1);
    ret = c - '0';
    while ((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + c - '0';
    return ret * w;
}

int main() {
    int n = read(), q = read();
    vector<int> A(n + 1, 0), B(n + 1, 0), N(n + 1, 0);
    bool found = false;
    int t = 0;

    // Read and process queries
    for (int i = 0; i < q; ++i) {
        int s = read(), t = read();
        if (s < t) {
            ++A[s - 1];
            --A[t - 1];
        } else if (s > t) {
            ++B[t];
            --B[s];
        }
    }

    // Calculate prefix sums
    for (int i = 1; i <= n; ++i) {
        A[i] += A[i - 1];
        B[i] += B[i - 1];
    }
    // Check if there's any overlap
    for (int i = 1; i <= n - 2; ++i) {
        if (A[i] && B[i]) {
            found = true;
            break;
        }
    }

    if (found) {
        cout << "QED" << endl;
        return 0;
    }
    // Assign numbers
    for (int i = 1; i <= n; ++i) {
        if (!N[i]) {
            int count = 1;
            for (int j = i; A[j] && j + 2 <= n; j += 2) {
                ++count;
            }
            for (int j = 1; j <= count; ++j) {
                N[i + 2 * count - 2 * j] = ++t;
            }
        }
    }
    // Print result
    for (int i = 1; i <= n; ++i) {
        cout << N[i];
        if (i != n) {
            cout << " ";
        } else {
            cout << endl;
        }
    }

    return 0;
}
