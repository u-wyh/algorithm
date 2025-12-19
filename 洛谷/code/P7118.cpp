#include<bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
const int MAXN = 1e6+5;

int n;
int f[MAXN];
long long ans=0;

int son[MAXN][2];
int sz[MAXN];

// 阶乘余数表
long long fac[MAXN];
// 阶乘逆元表
long long inv1[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

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
void build1(int n) {
	fac[0] = inv1[0] = 1;
	fac[1] = 1;
	for (int i = 2; i <= n; i++) {
		fac[i] = ((long long) i * fac[i - 1]) % MOD;
	}
	inv1[n] = power(fac[n], MOD - 2);
	for (int i = n - 1; i >= 1; i--) {
		inv1[i] = ((long long) (i + 1) * inv1[i + 1]) % MOD;
	}
}

long long c(int n, int k) {
	return (((fac[n] * inv1[k]) % MOD) * inv1[n - k]) % MOD;
}

int main()
{
    n=read();
    build1(2*n);
    for(int i=1;i<=n;i++){
        f[i]=(c(2 * i, i) - c(2 * i, i - 1) + MOD) % MOD;
        ans+=f[i];
        // cout<<f[i]<<' ';
    }
    ans-=f[n];
    for(int i=1;i<=n;i++){
        son[i][0]=read();
        son[i][1]=read();
    }
    return 0;
}