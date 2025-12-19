#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MOD = 1e9+7;

long long fac[MAXN];
// 阶乘逆元表
long long inv1[MAXN];
// 连续数逆元表
long long inv2[MAXN];

long long power(long long x, long long p) {
	long long ans = 1;
	while (p > 0) {
		if ((p & 1) == 1) {
			ans = (ans * x);
		}
		x = (x * x);
		p >>= 1;
	}
	return ans;
}

// 来自讲解099，题目3，生成阶乘余数表、阶乘逆元表
void build1(int n) {
	fac[0] = inv1[0] = 1;
	fac[1] = 1;
	for (int i = 2; i <= n; i++) {
		fac[i] = ((long long) i * fac[i - 1]);
	}
	inv1[n] = power(fac[n], MOD - 2);
	for (int i = n - 1; i >= 1; i--) {
		inv1[i] = ((long long) (i + 1) * inv1[i + 1]);
	}
}


long long c(int n, int k) {
	return (((fac[n] * inv1[k])) * inv1[n - k]);
}

// 公式1
long long compute1(int n) {
    build1(2 * n);
    return c(2 * n, n) - c(2 * n, n - 1) ;
}

int main()
{
    int n;
    cin>>n;
    cout<<compute1(n)<<endl;
    return 0;
}
