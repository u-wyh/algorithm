// 用途：合并模数不一定互质的同余式。
// 时间：O(k log M)。
// 空间：O(k)。
// 注意：模数为正且最小公倍数不超过 1e18；无解输出 -1。
// 例题：https://www.luogu.com.cn/problem/P4777
// 题意：模数不一定互质，求同时满足所有同余式的数。
// 思路：逐式解线性同余方程；差值不能被 gcd 整除则无解。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

long long m[MAXN];
long long r[MAXN];

long long d, x, y, px, py;

long long multiply(long long a, long long b, long long mod) {
    a %= mod;
    b %= mod;
    if (a < 0) a += mod;
    if (b < 0) b += mod;
    return (__int128)a * b % mod;
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

// 逐个合并同余式；当前解表示为 tail (mod lcm)。
long long excrt(int n) {
    long long tail = 0, lcm = 1, tmp, b, c, x0;
    for (int i = 1; i <= n; i++) {
        b = m[i];
        c = ((r[i] - tail) % b + b) % b;
        exgcd(lcm, b);
        if (c % d != 0) {
            return -1;
        }
        // 先检查差值可被 gcd 整除，再求新同余类的偏移。
        x0 = multiply(x, c / d, b / d);
        tmp = lcm * (b / d);
        tail = (tail + multiply(x0, lcm, tmp)) % tmp;
        lcm = tmp;
    }
    return tail;
}

int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>m[i]>>r[i];
    }
    cout<<excrt(n)<<endl;
    return 0;
}
