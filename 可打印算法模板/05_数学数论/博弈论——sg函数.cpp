// 用途：计算分糖豆博弈的 SG 值，统计能使对手必败的首步。
// 时间：O(n³)。
// 空间：O(n)。
// 例题：https://www.luogu.com.cn/problem/P3185
// 题意：给定糖豆分堆规则，求能让对手必败的首步数量。
// 思路：递归记忆化各状态 SG 值，异或判断转移后是否为 0。
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 21; // 最大瓶子数量
const int MAXV = 101; // SG 值的最大范围

int nums[MAXN]; // 每个瓶子中的糖豆数量
int sg[MAXN]; // 每个位置的 SG 值
bool appear[MAXV]; // 用于计算 SG 值的辅助数组

// 预处理 SG 值
void build() {
    for (int i = 1; i < MAXN; i++) {
        memset(appear, false, sizeof(appear)); // 重置 appear 数组
        for (int j = i - 1; j >= 0; j--) {
            for (int k = j; k >= 0; k--) {
                appear[sg[j] ^ sg[k]] = true; // 标记 SG 值的组合
            }
        }
        for (int s = 0; s < MAXV; s++) {
            if (!appear[s]) {
                sg[i] = s; // 找到最小的未出现的 SG 值
                break;
            }
        }
    }
}

// 计算当前状态的解
string compute(int n) {
    int eor = 0; // 所有糖果的 SG 值异或和
    for (int i = n - 1; i >= 0; i--) {
        if (nums[i] % 2 == 1) {
            eor ^= sg[i]; // 奇数个糖豆才参与异或
        }
    }
    if (eor == 0) {
        return "-1 -1 -1\n0"; // 无法获胜
    }
    int cnt = 0, a = -1, b = -1, c = -1, pos;
    for (int i = n - 1; i >= 1; i--) {
        if (nums[i] > 0) {
            for (int j = i - 1; j >= 0; j--) {
                for (int k = j; k >= 0; k--) {
                    pos = eor ^ sg[i] ^ sg[j] ^ sg[k]; // 计算新的 SG 值
                    if (pos == 0) {
                        cnt++; // 统计可行解的数量
                        if (a == -1) {
                            a = i;
                            b = j;
                            c = k; // 记录字典序最小的解
                        }
                    }
                }
            }
        }
    }
    return to_string(n - 1 - a) + " " + to_string(n - 1 - b) + " " + to_string(n - 1 - c) + "\n" + to_string(cnt);
}

int main() {
    build(); // 预处理 SG 值
    int t, n;
    cin >> t; // 测试用例数量
    while (t--) {
        cin >> n; // 瓶子数量
        for (int j = n - 1; j >= 0; j--) {
            cin >> nums[j]; // 输入每个瓶子中的糖豆数量
        }
        cout << compute(n) << endl; // 输出结果
    }
    return 0;
}
