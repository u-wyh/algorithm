// 背包(两次转圈法)
// 一共有n种物品，第i种物品的体积为v[i]，价值为c[i]，每种物品可以选择任意个，个数不能是负数
// 一共有m条查询，每次查询都会给定jobv，代表体积的要求
// 要求挑选物品的体积和一定要严格是jobv，返回能得到的最大价值和
// 如果没有方案能正好凑满jobv，返回-1
// 1 <= n <= 50
// 1 <= m <= 10^5
// 1 <= v[i] <= 10^5
// 1 <= c[i] <= 10^6
// 10^11 <= jobv <= 10^12
// 测试链接 : https://www.luogu.com.cn/problem/P9140
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const long long inf = LLONG_MIN; // 使用 LLONG_MIN 表示负无穷

int v[MAXN]; // 物品体积
int c[MAXN]; // 物品价值
// dp[i] : 总体积为某数，先尽可能用基准物品填入，剩余的体积为i
// 可以去掉若干基准物品，加入若干其他物品，最终凑齐总体积
// 能获得的最大补偿是多少
long long dp[MAXN]; // dp 数组

int n, m, x, y;

// 计算最大公约数
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// 计算 dp 数组  这个实际上是最长路
void compute() {
    fill(dp, dp + x, inf); // 初始化 dp 数组为负无穷
    dp[0] = 0; // 体积为 0 时，价值为 0

    for (int i = 1; i <= n; i++) {
        if (v[i] != x) { // 跳过基准物品
            int d = gcd(v[i], x); // 计算最大公约数
            for (int j = 0; j < d; j++) {
                for (int cur = j, next, circle = 0; circle < 2; circle += (cur == j ? 1 : 0)) {
                    next = (cur + v[i]) % x; // 计算下一个状态
                    if (dp[cur] != inf) { // 如果当前状态可达
                        dp[next] = max(dp[next], dp[cur] - (long long)((cur + v[i]) / x) * y + c[i]);
                    }
                    cur = next; // 更新当前状态
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false); // 加速输入输出
    cin.tie(nullptr);

    cin >> n >> m;

    double best = 0, ratio;
    for (int i = 1; i <= n; i++) {
        cin >> v[i] >> c[i];
        ratio = (double)c[i] / v[i]; // 计算性价比
        if (ratio > best) { // 找到性价比最高的物品
            best = ratio;
            x = v[i]; // 基准物品体积
            y = c[i]; // 基准物品价值
        }
    }

    compute(); // 计算 dp 数组

    long long jobv;
    for (int i = 1; i <= m; i++) {
        cin >> jobv;
        int remainder = jobv % x; // 计算余数
        if (dp[remainder] == inf) { // 如果余数状态不可达
            cout << "-1\n";
        } else {
            cout << (jobv / x) * y + dp[remainder] << "\n"; // 输出最大价值
        }
    }

    return 0;
}
