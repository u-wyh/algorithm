// https://www.luogu.com.cn/problem/P3230
// 题意：输入球队数量 N，以及 N 支球队各自的最终联赛总得分。
// 每两支球队间恰好比赛一场，胜者得 3 分、败者 0 分、平局各得 1 分，
// 求符合最终得分的可能比赛胜负平过程方案数。
// 输出方案数对 10^9+7 取模的结果。
// 数据范围：3 <= N <= 10，保证至少存在一组解。
// 难度评分：1800（洛谷分级换算）
// 算法标签：记忆化搜索、深度优先搜索
#include <cstdio>
#include <map>
#include <algorithm>
#include <iostream>

const int MAXN = 15;
const int MOD = 1000000007;
using namespace std;

typedef long long ll;

ll stones[MAXN];
map<ll, ll> memo;

bool compare(int a, int b) {
    return a > b; // Sort in descending order for optimization
}

ll hashState(int count) {
    ll result = 0;
    ll sortedStones[MAXN];
    for (int i = 0; i < count; ++i) {
        sortedStones[i] = stones[i + 1];
    }
    sort(sortedStones, sortedStones + count, compare);
    for (int i = 0; i < count; ++i) {
        result = result * 28 + sortedStones[i]; // Use base 28 for hashing
    }
    return result;
}

ll dfs(int current, int total) {
    if (stones[current] > 3 * (total - current)) return -1; // Early exit if impossible

    if (current == total) {
        if (total == 1) return 1; // Base case: one stone left
        ll hashValue = hashState(total - 1);
        if (memo.count(hashValue)) return memo[hashValue];
        return memo[hashValue] = dfs(1, total - 1);
    }

    ll result = 0;

    // Remove 3 stones from the current pile
    if (stones[current] >= 3) {
        stones[current] -= 3;
        ll temp = dfs(current + 1, total);
        if (temp != -1) result = (result + temp) % MOD;
        stones[current] += 3;
    }

    // Move one stone from the current pile to the next pile
    if (stones[current] > 0 && stones[current + 1] > 0) {
        stones[current]--;
        stones[current + 1]--;
        ll temp = dfs(current + 1, total);
        if (temp != -1) result = (result + temp) % MOD;
        stones[current]++;
        stones[current + 1]++;
    }

    // Remove 3 stones from the next pile (simulate moving 3 to current and then removing from there)
    if (stones[current + 1] >= 3) {
        stones[current + 1] -= 3;
        ll temp = dfs(current + 1, total);
        if (temp != -1) result = (result + temp) % MOD;
        stones[current + 1] += 3;
    }

    return result != 0 ? result : -1;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &stones[i]);
    }
    sort(stones + 1, stones + n + 1, compare);
    printf("%lld\n", dfs(1, n));
    return 0;
}
