// https://www.luogu.com.cn/problem/P7118
// 题意：每个 Galgame 为以 1 为根的二叉树（左儿子为 A 场景，右儿子为 B 场景，0 表示空场景）。
// 按「可达场景数更多 -> A 场景更有趣 -> B 场景更有趣」的规则定义场景偏序；
// 给定一款 n 场景的 Galgame，求所有本质不同且不如它有趣的 Galgame 数量，对 998244353 取模。
// 数据范围：1 <= n <= 10^6，0 <= a_i, b_i <= n。
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