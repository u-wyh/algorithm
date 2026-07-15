#include<bits/stdc++.h>
#define int long long
using namespace std;

inline int read() {
    int w = 1, s = 0; 
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') w = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        s = s * 10 + (ch - '0');
        ch = getchar();
    }
    return w * s;
}

const int mod = 998244353;    
const int maxn = 500 + 10;
const int inf = 1e13 + 7;

int n, m;
int dp[maxn][maxn], sum[maxn][maxn], a[maxn][maxn];

int ask(int l1, int r1, int l2, int r2) {
    return sum[l2][r2] - sum[l1 - 1][r2] - sum[l2][r1 - 1] + sum[l1 - 1][r1 - 1];
}

void Main() {
    n = read(), m = read();
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            a[i][j] = sum[i][j] = 0;
        }
    }
    
    bool ff = 1;
    for (int i = 1; i <= m; i++) {
        int x = read(), y = read();
        a[x][y] = 1;
        if (x == y) ff = 0;
    }
    
    if (!ff) {
        puts("0");
        return;
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            sum[i][j] = a[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }
    
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        dp[i][i] = 1;
    }
    
    for (int len = 2; len <= n; len++) {
        for (int l = 1; l <= n - len + 1; l++) {
            int r = l + len - 1;
            
            // Case 1: Place l in its own cycle
            if (!ask(l, l + 1, l, r)) {
                dp[l][r] = (dp[l][r] + dp[l + 1][r]) % mod;
            }
            
            // Case 2: Place r in its own cycle
            if (!ask(l + 1, l, r, l)) {
                dp[l][r] = (dp[l][r] + dp[l + 1][r]) % mod;
            }
            
            // Case 3: Split into two intervals
            for (int k = l + 1; k < r; k++) {
                if (!ask(l, l + 1, l, k) && !ask(k + 1, l, r, k)) {
                    dp[l][r] = (dp[l][r] + dp[l + 1][k] * dp[k + 1][r] % mod) % mod;
                }
            }
        }
    }
    
    printf("%lld\n", dp[1][n]);
}

signed main() {
    int T = read();
    while (T--) {
        Main();
    }
    return 0;
}