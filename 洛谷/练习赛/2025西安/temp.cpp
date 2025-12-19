#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    vector<long long> dp(n + 1, 0);
    dp[0] = 1;
    
    for (int i = 0; i < n; i++) {
        vector<long long> new_dp(n + 1, 0);
        for (int j = 0; j <= i; j++) {
            if (dp[j] == 0) continue;
            if (a[i] == -1) {
                if (j > 0) {
                    new_dp[j - 1] = (new_dp[j - 1] + dp[j] * j % MOD) % MOD;
                }
                new_dp[j] = (new_dp[j] + dp[j] * (m - j) % MOD) % MOD;
            } else {
                int x = a[i];
                if (x > j) {
                    new_dp[0] = (new_dp[0] + dp[j]) % MOD;
                } else if (x == j) {
                    if (j > 0) {
                        new_dp[j - 1] = (new_dp[j - 1] + dp[j]) % MOD;
                    } else {
                        new_dp[0] = (new_dp[0] + dp[j]) % MOD;
                    }
                } else {
                    new_dp[j - x] = (new_dp[j - x] + dp[j]) % MOD;
                }
            }
        }
        dp = move(new_dp);
    }
    
    cout << dp[0] << endl;
    
    return 0;
}