// https://acm.hdu.edu.cn/showproblem.php?pid=1573
#include<bits/stdc++.h>
using namespace std;
#define int long long

int limit,n;
int m[11];
int r[11];

long long d, x, y, px, py;

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

int excrt(){
    long long tail = 0, lcm = 1, tmp, b, c, x0;
    // ans = lcm * x + tail
    for (int i = 1; i <= n; i++) {
        // ans = m[i] * y + ri
        // lcm * x + m[i] * y = ri - tail
        // a = lcm
        // b = m[i]
        // c = ri - tail
        b = m[i];
        c = ((r[i] - tail) % b + b) % b;
        exgcd(lcm, b);
        if (c % d != 0) {
            return 0;
        }
        // ax + by = gcd(a,b)，特解是，x变量
        // ax + by = c，特解是，x变量 * (c/d)
        // ax + by = c，最小非负特解x0 = (x * (c/d)) % (b/d) 取非负余数
        // 通解 = x0 + (b/d) * n
        x0 = (x*c / d)%( b / d);
        // ans = lcm * x + tail，带入通解
        // ans = lcm * (x0 + (b/d) * n) + tail
        // ans = lcm * (b/d) * n + lcm * x0 + tail
        // tail' = tail' % lcm'
        tmp = lcm * (b / d);
        tail = (tail + ((x0*lcm)% tmp)) % tmp;
        lcm = tmp;
    }
    tail=(tail+tmp)%tmp;
    if(tail == 0){
        tail = lcm;
    }

    if(tail>limit){
        return 0;
    }
    else{
        return 1+(limit-tail)/lcm;
    }
}

void solve(){
    cin>>limit>>n;
    for(int i=1;i<=n;i++){
        cin>>m[i];
    }
    for(int i=1;i<=n;i++){
        cin>>r[i];
    }
    cout<<excrt()<<endl;
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}