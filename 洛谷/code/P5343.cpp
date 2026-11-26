// https://www.luogu.com.cn/problem/P5343
// 题意：将长度为 n 的序列划分为若干连续块，PinkRabbit 允许 PR 种块长、NaCly_Fish 允许 NF 种块长（各自列表中可能有重复）。
// 只能使用两人都允许的块长进行划分，求不同分块方案数对 10^9+7 取模。
// 数据范围：1 <= n <= 10^18，1 <= PR, NF, x <= 100（x 为最大块长）。
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

const int MOD = 1e9 + 7;

int n, pr, nf, m, cnt = 0;
vector<int> ans;
vector<int> f(105, 0);
map<int, int> graph;

vector<vector<int>> multiply(vector<vector<int>>& a, vector<vector<int>>& b) {
    int n = a.size();
    int m = b[0].size();
    vector<vector<int>> ans(n, vector<int>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < n; ++k) { // Note: Here we assume both matrices are square, adjust if necessary
                ans[i][j] = (ans[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return ans;
}

vector<vector<int>> power(vector<vector<int>>& m, long long p) {
    int n = m.size();
    vector<vector<int>> ans(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        ans[i][i] = 1;
    }
    while (p > 0) {
        if (p % 2 == 1) {
            ans = multiply(ans, m);
        }
        m = multiply(m, m);
        p /= 2;
    }
    return ans;
}

int main() {
    cin >> n >> pr;
    for (int x, i = 0; i < pr; ++i) {
        cin >> x;
        graph[x] = 1;
    }
    cin >> nf;
    for (int x, i = 0; i < nf; ++i) {
        cin >> x;
        if (graph[x]) {
            ans.push_back(x);
        }
    }
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end()); // Remove duplicates

    int size = ans.back() + 1;
    vector<vector<int>> base(size, vector<int>(size, 0));
    for (int i = 0; i < ans.size(); ++i) {
        base[0][ans[i]] = 1; // Adjust index according to your needs, here assuming base[0][...] is the start row
    }
    for (int i = 0; i < size - 1; ++i) {
        base[i + 1][i] = 1;
    }

    // DP preprocessing (adjusted for vector usage and indexing)
    f[0] = 1;
    for (int i = 1; i < size; ++i) {
        for (int j : ans) {
            if (j <= i) {
                f[i] = (f[i] + f[i - j]) % MOD;
            }
        }
    }

    vector<vector<int>> init_mat(size, vector<int>(2, 0));
    for (int i = 0; i < size; ++i) {
        init_mat[i][1] = f[size - 1 - i]; // Adjust indexing as needed
    }

    vector<vector<int>> result_mat = multiply(power(base, n - 1), init_mat); // Adjust exponent and matrices as needed

    cout << result_mat[0][1] << endl; // Output the result, adjust indexing as needed
    return 0;
}
