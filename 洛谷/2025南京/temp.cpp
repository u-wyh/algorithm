#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;

int main() {
    string s;
    cin >> s;
    int n = s.length();
    
    // 预处理LCP
    vector<vector<int>> lcp(n + 1, vector<int>(n + 1, 0));
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            if (s[i] == s[j]) {
                lcp[i][j] = lcp[i + 1][j + 1] + 1;
            }
        }
    }
    
    // 预处理相同子串对的数量
    vector<vector<long long>> same(n + 1, vector<long long>(n + 1, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            int common = lcp[i][j];
            for (int len = 1; len <= common; len++) {
                if (i + len <= n && j + len <= n) {
                    same[i][i + len - 1]++;
                }
            }
        }
    }
    
    long long ans = 0;
    
    // 枚举所有可能的第二个和第三个区间
    for (int i2 = 0; i2 < n; i2++) {
        for (int j2 = i2; j2 < n; j2++) {
            // 枚举第二个区间的严格后缀
            for (int k = i2 + 1; k <= j2; k++) {
                int suffix_len = j2 - k + 1;
                int i3 = j2 + 1;
                
                // 找所有可能的第三个区间位置
                while (i3 + suffix_len - 1 < n) {
                    if (lcp[k][i3] >= suffix_len) {
                        // 计算第一个和第四个区间的可能数量
                        for (int i1 = 0; i1 < i2; i1++) {
                            for (int j1 = i1; j1 < i2; j1++) {
                                int len1 = j1 - i1 + 1;
                                int i4 = i3 + suffix_len;
                                
                                // 找所有可能的第四个区间
                                while (i4 + len1 - 1 < n) {
                                    if (lcp[i1][i4] >= len1) {
                                        ans = (ans + 1) % MOD;
                                    }
                                    i4++;
                                }
                            }
                        }
                    }
                    i3++;
                }
            }
        }
    }
    
    cout << ans << endl;
    return 0;
}
/*
penpineappleapplepen
*/