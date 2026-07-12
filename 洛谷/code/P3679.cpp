// P3679 [CERC2016] 二分毯 Bipartite Blanket
// 核心结论：点集 V = S ∪ T (S⊆A, T⊆B) 能被匹配覆盖 ⇔ S 和 T 各自都能被匹配覆盖
// 步骤：
//   1. 用霍尔定理 + SOS DP 找出 A、B 两侧所有"可匹配"的子集
//   2. 收集它们的权值
//   3. 排序后双指针统计 wa + wb ≥ t 的对数

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> adjA(n, 0), adjB(m, 0);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < m; ++j) {
            if (s[j] == '1') {
                adjA[i] |= (1 << j);
                adjB[j] |= (1 << i);
            }
        }
    }

    vector<long long> valA(n), valB(m);
    for (int i = 0; i < n; ++i) cin >> valA[i];
    for (int j = 0; j < m; ++j) cin >> valB[j];

    long long t;
    cin >> t;

    // ------- A 侧：找出所有可匹配的子集 -------
    int szA = 1 << n;
    vector<int> neiA(szA, 0), fA(szA, 0);      // fA[mask] = |mask| - |N(mask)|
    vector<long long> sumA(szA, 0);
    vector<long long> wtA;                      // 可匹配子集的权值

    for (int mask = 1; mask < szA; ++mask) {
        int lb = mask & -mask;
        int i = __builtin_ctz(lb);
        int prev = mask ^ lb;
        neiA[mask] = neiA[prev] | adjA[i];
        sumA[mask] = sumA[prev] + valA[i];
        fA[mask] = __builtin_popcount(mask) - __builtin_popcount(neiA[mask]);
    }

    // SOS DP：gA[mask] = max over submask ⊆ mask of fA[submask]
    vector<int> gA = fA;
    for (int i = 0; i < n; ++i) {
        for (int mask = 0; mask < szA; ++mask) {
            if (mask >> i & 1) {
                gA[mask] = max(gA[mask], gA[mask ^ (1 << i)]);
            }
        }
    }

    for (int mask = 0; mask < szA; ++mask) {
        if (gA[mask] <= 0) wtA.push_back(sumA[mask]);
    }

    // ------- B 侧同理 -------
    int szB = 1 << m;
    vector<int> neiB(szB, 0), fB(szB, 0);
    vector<long long> sumB(szB, 0);
    vector<long long> wtB;

    for (int mask = 1; mask < szB; ++mask) {
        int lb = mask & -mask;
        int i = __builtin_ctz(lb);
        int prev = mask ^ lb;
        neiB[mask] = neiB[prev] | adjB[i];
        sumB[mask] = sumB[prev] + valB[i];
        fB[mask] = __builtin_popcount(mask) - __builtin_popcount(neiB[mask]);
    }

    vector<int> gB = fB;
    for (int i = 0; i < m; ++i) {
        for (int mask = 0; mask < szB; ++mask) {
            if (mask >> i & 1) {
                gB[mask] = max(gB[mask], gB[mask ^ (1 << i)]);
            }
        }
    }

    for (int mask = 0; mask < szB; ++mask) {
        if (gB[mask] <= 0) wtB.push_back(sumB[mask]);
    }

    // ------- 双指针统计 -------
    sort(wtA.begin(), wtA.end());
    sort(wtB.begin(), wtB.end());

    long long ans = 0;
    int j = (int)wtB.size() - 1;
    for (long long wa : wtA) {
        while (j >= 0 && wa + wtB[j] >= t) --j;
        ans += wtB.size() - 1 - j;
    }

    cout << ans << '\n';
    return 0;
}
