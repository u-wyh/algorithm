// https://www.luogu.com.cn/problem/P3868
// 题意：第一行输入组数 k，第二行输入 k 个整数 a_1..a_k，第三行输入 k 个两两互素的正整数 b_1..b_k。
// 求最小的非负整数 n（n in N），满足对所有 i in [1, k] 均有 b_i | (n - a_i)。
// 输出一行一个整数表示答案 n。
// 数据范围：对于 100% 的数据，1 <= k <= 10，|a_i| <= 10^9，1 <= b_i <= 6 * 10^3
// prod_{i=1}^k b_i <= 10^18。
#include<bits/stdc++.h>
// 算法标签：中国剩余定理、扩展欧几里得、龟速乘
using namespace std;
#define int long long

int n;
int a[11];
int b[11];
int maxv;

long long d, x, y, px, py;

// 原理来自，讲解033，位运算实现乘法
// a * b的过程自己实现，每一个中间过程都%mod
// 这么写目的是防止溢出，也叫龟速乘
long long multiply(long long a, long long b, long long mod) {
	// 既然是在%mod的意义下，那么a和b可以都转化成非负的
	// 本题不转化无所谓，但是其他题目可能需要转化
	// 尤其是b需要转化，否则while循环会跑不完
	a = (a % mod + mod) % mod;
	b = (b % mod + mod) % mod;
	long long ans = 0;
	while (b != 0) {
		if ((b & 1) != 0) {
			ans = (ans + a) % mod;
		}
		a = (a + a) % mod;
		b >>= 1;
	}
	return ans;
}

void exgcd(long long a, long long b) {
    if (b == 0) {
        d = a;
        x = 1;
        y = 0;
    } else {
        exgcd(b, a % b);
        px = x;
        py = y;
        x = py;
        y = px - py * (a / b);
    }
}

// 中国剩余定理模版
long long crt() {
    long long lcm = 1;
    for (int i = 1; i <= n; i++) {
        lcm = lcm * b[i];
    }
    long long ai, ci, ans = 0;
    for (int i = 1; i <= n; i++) {
        // ai = lcm / m[i]
        ai = lcm / b[i];
        // ai逆元，在%m[i]意义下的逆元
        exgcd(ai, b[i]);
        // ci = (ri * ai * ai逆元) % lcm
        ci = multiply(a[i], multiply(ai, x, lcm), lcm);
        ans = (ans + ci) % lcm;
    }

    return ans;
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        maxv=max(maxv,a[i]);
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
        a[i]%=b[i];
    }
    cout<<crt()<<endl;
    return 0;
}