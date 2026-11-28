// https://www.luogu.com.cn/problem/P10419
// 题意：给一个部分填好的 N×N 棋盘。
// 固定数字不能改，空格填 0 或 1。
// 每行每列的两种数字各占一半，
// 横竖都不能连续出现三个相同的数字。
// 任意两行不同，任意两列也不同。
// 输出：逐行输出唯一解，每格之间不加空格。
// 数据范围：2 <= N <= 10，N 为偶数。
// 输入字符仅为 0、1 或下划线。
// 难度评分：1400（洛谷分级换算）
// 算法标签：状态压缩、约束传播、回溯

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;
const int MAX_PATTERNS = 252;
using Domain = bitset<MAX_PATTERNS>;
using Domains = array<Domain, 2 * MAXN>;

int n, patternCount;
int patterns[MAX_PATTERNS];
Domain allowed[2][MAXN];

bool restrictDomain(Domain& domain, const Domain& mask, bool& changed){
    Domain reduced = domain & mask;
    if (reduced != domain){
        domain = reduced;
        changed = true;
    }
    return domain.any();
}

bool propagate(Domains& domains){
    bool changed;
    do {
        changed = false;
        for (int i = 0; i < 2 * n; ++i){
            int count = domains[i].count();
            if (count == 0){
                return false;
            }
            if (count == 1){
                int first = i < n ? 0 : n;
                for (int j = first; j < first + n; ++j){
                    if (j != i && !restrictDomain(domains[j], ~domains[i], changed)){
                        return false;
                    }
                }
            }
        }

        // 每个格子的行候选与列候选必须给出相同数字。
        for (int r = 0; r < n; ++r){
            for (int c = 0; c < n; ++c){
                for (int digit = 0; digit < 2; ++digit){
                    if ((domains[r] & allowed[digit][c]).none() &&
                        !restrictDomain(domains[n + c], allowed[digit ^ 1][r], changed)){
                        return false;
                    }
                    if ((domains[n + c] & allowed[digit][r]).none() &&
                        !restrictDomain(domains[r], allowed[digit ^ 1][c], changed)){
                        return false;
                    }
                }
            }
        }
    } while (changed);
    return true;
}

bool solve(Domains& domains){
    if (!propagate(domains)){
        return false;
    }
    int choice = -1;
    int fewest = MAX_PATTERNS + 1;
    for (int i = 0; i < 2 * n; ++i){
        int count = domains[i].count();
        if (count > 1 && count < fewest){
            choice = i;
            fewest = count;
        }
    }
    if (choice == -1){
        return true;
    }

    for (int i = 0; i < patternCount; ++i){
        if (domains[choice].test(i)){
            Domains next = domains;
            next[choice].reset();
            next[choice].set(i);
            if (solve(next)){
                domains = next;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    Domain all;
    for (int mask = 0; mask < (1 << n); ++mask){
        if (__builtin_popcount(mask) != n / 2){
            continue;
        }
        int zeros = mask ^ ((1 << n) - 1);
        if ((mask & (mask >> 1) & (mask >> 2)) ||
            (zeros & (zeros >> 1) & (zeros >> 2))){
            continue;
        }
        patterns[patternCount] = mask;
        all.set(patternCount);
        for (int i = 0; i < n; ++i){
            allowed[(mask >> i) & 1][i].set(patternCount);
        }
        ++patternCount;
    }

    Domains domains;
    domains.fill(all);
    for (int r = 0; r < n; ++r){
        for (int c = 0; c < n; ++c){
            char ch;
            cin >> ch;
            if (ch != '_'){
                domains[r] &= allowed[ch - '0'][c];
                domains[n + c] &= allowed[ch - '0'][r];
            }
        }
    }

    if (solve(domains)){
        for (int r = 0; r < n; ++r){
            int p = 0;
            while (!domains[r].test(p)){
                ++p;
            }
            for (int c = 0; c < n; ++c){
                cout << ((patterns[p] >> c) & 1);
            }
            cout << '\n';
        }
    }
    return 0;
}
