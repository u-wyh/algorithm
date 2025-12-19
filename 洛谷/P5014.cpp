#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 998244353;
const int MAXN = 2e6+5;

// 阶乘余数表
long long fac[MAXN];
// 阶乘逆元表
long long inv[MAXN];

long long power(long long x, long long p) {
	long long ans = 1;
	while (p > 0) {
		if ((p & 1) == 1) {
			ans = (ans * x) % MOD;
		}
		x = (x * x) % MOD;
		p >>= 1;
	}
	return ans;
}

// 来自讲解099，题目3，生成阶乘余数表、阶乘逆元表
void build(int n) {
	fac[0] = inv[0] = 1;
	fac[1] = 1;
	for (int i = 2; i <= n; i++) {
		fac[i] = ((long long) i * fac[i - 1]) % MOD;
	}
	inv[n] = power(fac[n], MOD - 2);
	for (int i = n - 1; i >= 1; i--) {
		inv[i] = ((long long) (i + 1) * inv[i + 1]) % MOD;
	}
}

long long c(int n, int k) {
	return (((fac[n] * inv[k]) % MOD) * inv[n - k]) % MOD;
}

signed main()
{
    build(MAXN);
    int t;
    cin>>t;
    while(t--){
        int x;
        cin>>x;
        int n = sqrt(x);
		while (n * (n + 1) / 2 < x)
            n ++ ;
		int m = x - (n * (n - 1) / 2);
		int ans = 0;
		n -- , m -- ;
		for (int i = 0; i <= m; i ++ ) {
			int n0 = n - i, m0 = m - i;
			(ans += (c(n0 + m0, m0) - c(n0 + m0, m0 - 1) + MOD) % MOD * c(n0 + m0 + i, i) % MOD) %= MOD;
		}
		cout<<ans<<endl;
    }
    return 0;
}
