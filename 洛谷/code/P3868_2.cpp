// https://www.luogu.com.cn/problem/P3868
#include<bits/stdc++.h>
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