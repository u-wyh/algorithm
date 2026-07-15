#include <iostream>
#define MOD 1000000007
using namespace std;

int testCases;
string inputString;
long long dp[110][5000]; // dp[i][j] 表示前 i 个字符，和为 j 的种类数

int main() {
    cin >> testCases;
    // 初始化：单个字符时，其 ASCII 值减去 'a' 的结果即为对应的和
    for (int i = 0; i < 26; i++) {
        dp[1][i] = 1;
    }

    // 动态规划填充 dp 数组
    for (int length = 2; length <= 100; length++) {
        dp[length][0] = 1; // 任何长度的字符串，和为 0 的情况只有一种（即不包含任何字符）
        for (int sum = 1; sum <= 2700; sum++) {
            for (int charValue = 0; charValue < 26; charValue++) { // 'a' 到 'z' 的 ASCII 差值
                if (sum - charValue >= 0) {
                    dp[length][sum] = (dp[length][sum] % MOD + dp[length - 1][sum - charValue] % MOD) % MOD;
                }
            }
        }
    }

    // 处理每个测试用例
    while (testCases--) {
        cin >> inputString;
        int stringSum = 0;
        for (char c : inputString) {
            stringSum += c - 'a'; // 计算字符串中所有字符对应的和
        }
        // 输出结果，减去 1 是因为我们要排除空字符串的情况（和为 0 的情况已经在 dp 中考虑）
        cout << (dp[inputString.size()][stringSum] % MOD - 1 + MOD) % MOD << endl; // 使用 (x + MOD) % MOD 防止负数
    }

    return 0;
}
