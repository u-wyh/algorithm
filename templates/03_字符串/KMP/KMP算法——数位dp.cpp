// 找到所有好字符串
// 给你两个长度为n的字符串s1和s2，以及一个字符串evil
// 好字符串的定义为 : 长度为n，字典序大于等于s1，字典序小于等于s2，且不包含evil字符串
// 返回好字符串的数量
// 由于答案可能很大，答案对 1000000007 取模
// 测试链接 : https://leetcode.cn/problems/find-all-good-strings/
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int MOD = 1000000007; // 模数
const int MAXN = 505;      // 字符串最大长度
const int MAXM = 55;       // evil 字符串最大长度

int dp[MAXN][MAXM][2];     // DP 数组，dp[i][j][free] 表示处理到第 i 位，KMP 状态为 j，是否自由选择（free）时的方案数
int nxt[MAXM];             // KMP 的 next 数组

class Solution {
public:
    // 清空 DP 数组
    void clear(int n, int m) {
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                dp[i][j][0] = -1; // 初始化为 -1 表示未计算
                dp[i][j][1] = -1;
            }
        }
    }

    // 主函数：计算好字符串的数量
    int findGoodStrings(int n, string str1, string str2, string evil) {
        char* s1 = &str1[0]; // 转换为 C 风格字符串
        char* s2 = &str2[0];
        char* e = &evil[0];
        int m = evil.size(); // evil 的长度

        // 构建 evil 的 next 数组
        nextArray(e, m);
        // 清空 DP 数组
        clear(n, m);
        // 计算小于等于 s2 的好字符串数量
        int ans = f(s2, e, n, m, 0, 0, 0);
        
        clear(n, m);
        // 减去小于等于 s1 的好字符串数量，并处理负数取模
        ans = (ans - f(s1, e, n, m, 0, 0, 0) + MOD) % MOD;
        
        // 如果 s1 本身不包含 evil，则需要加回（因为被减掉了）
        if (kmp(s1, e, n, m) == -1) {
            ans = (ans + 1) % MOD;
        }
        return ans;
    }

    // 检查字符串 s 是否包含 evil 子串
    int kmp(char* s, char* e, int n, int m) {
        if (m == 0) return -1; // evil 为空，视为不包含
        int x = 0, y = 0;
        while (x < n && y < m) {
            if (s[x] == e[y]) {
                x++;
                y++;
            } else if (y == 0) {
                x++;
            } else {
                y = nxt[y]; // 使用 next 数组跳转
            }
        }
        return y == m ? x - y : -1; // 返回匹配起始位置，未匹配返回 -1
    }

    // 构建 KMP 的 next 数组
    void nextArray(char* e, int m) {
        if (m == 0) return;
        nxt[0] = -1; // 初始化
        if (m == 1) return;
        nxt[1] = 0;
        int i = 2, cn = 0; // cn 表示当前最长公共前后缀长度
        while (i < m) {
            if (e[i - 1] == e[cn]) {
                nxt[i++] = ++cn;
            } else if (cn > 0) {
                cn = nxt[cn]; // 回退
            } else {
                nxt[i++] = 0;
            }
        }
    }

    // 记忆化搜索：计算小于等于字符串 s 的好字符串数量
    int f(char* s, char* e, int n, int m, int i, int j, int free) {
        // j 达到 m 表示已匹配 evil，返回 0
        if (j == m) return 0;
        // 已构造完字符串，返回 1
        if (i == n) return 1;
        // 如果已计算，直接返回
        if (dp[i][j][free] != -1) return dp[i][j][free];
        
        long long ans = 0;
        char cur = s[i]; // 当前字符的上限
        
        if (free == 0) { // 当前受限（必须小于等于 s[i]）
            // 选择小于 cur 的字符
            for (char pick = 'a'; pick < cur; pick++) {
                // 更新 KMP 状态
                int new_j = jump(pick, e, j, m);
                // 后续自由选择
                ans = (ans + f(s, e, n, m, i + 1, new_j, 1)) % MOD;
            }
            // 选择等于 cur 的字符
            int new_j = jump(cur, e, j, m);
            // 后续仍然受限
            ans = (ans + f(s, e, n, m, i + 1, new_j, 0)) % MOD;
        } else { // 自由选择（可选任意字符）
            for (char pick = 'a'; pick <= 'z'; pick++) {
                int new_j = jump(pick, e, j, m);
                ans = (ans + f(s, e, n, m, i + 1, new_j, 1)) % MOD;
            }
        }
        
        dp[i][j][free] = ans; // 记忆化
        return ans;
    }

    // 辅助函数：根据当前状态和字符，跳转到下一个 KMP 状态
    int jump(char pick, char* e, int j, int m) {
        // 当 j 不为 -1 且（j 已达到 m 或当前字符不匹配）时，回退
        while (j != -1 && (j == m || pick != e[j])) {
            j = nxt[j];
        }
        return j + 1; // 匹配成功，状态 +1
    }
};

int main() {
    int n;
    string s1, s2, evil;
    cin >> n;
    cin >> s1 >> s2 >> evil;
    
    Solution sol;
    cout << sol.findGoodStrings(n, s1, s2, evil) << endl;
    
    return 0;
}