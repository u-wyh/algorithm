// 用途：合并两两互质的同余式 x≡r_i (mod m_i)。
// 时间：O(k log M)。
// 空间：O(k)。
// 注意：模数为正且乘积不超过 1e18。
// 例题：https://www.luogu.com.cn/problem/P1495
// 题意：求同时满足多条互质模数同余式的最小非负数。
// 思路：用扩展欧几里得逐步合并模数与余数。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 11;

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

// 每项用总模数除以当前模数，再乘该因子的逆元。
long long crt(int n) {
    long long lcm = 1;
    for (int i = 1; i <= n; i++) {
        lcm = lcm * m[i];
    }
    long long ai, ci, ans = 0;
    for (int i = 1; i <= n; i++) {
        ai = lcm / m[i];
        exgcd(ai, m[i]);
        ci = multiply(r[i], multiply(ai, x, lcm), lcm);
        ans = (ans + ci) % lcm;
    }
    return ans;
}

int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>m[i]>>r[i];
    }
    cout<<crt(n)<<endl;
    return 0;
}
