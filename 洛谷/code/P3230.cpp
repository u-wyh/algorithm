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
