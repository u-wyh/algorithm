#include<bits/stdc++.h>
using namespace std;
typedef long long _INT128;
const int MAXN = 1000001;

__int128 read() {
  char c = getchar();
  __int128 x = 0;
  bool f = 0;
  for (; !isdigit(c); c = getchar()) f ^= !(c ^ 45);
  for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
  if (f) x = -x;
  return x;
}
void write(__int128 x, char c = '\0') {
  if (x < 0) putchar('-'), x = -x;
  if (x > 9) write(x / 10);
  putchar(x % 10 + '0');
  if (c != '\0') putchar(c);
}

long long m;
long long r[MAXN];
long long res[MAXN];

long long d, x, y, px, py;

long long multiply(long long a, long long b, long long mod) {
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

// 扩展中国剩余定理模版
// 可以用于解决模数不是互质的情况  适用范围更广
long long excrt(int n) {
    long long tail = 0, lcm = 1, tmp, b, c, x0;
    // ans = lcm * x + tail
    for (int i = 1; i <= n; i++) {
        b = m;
        c = ((r[i] - tail) % b + b) % b;
        exgcd(lcm, b);
        if (c % d != 0) {
            return -1;
        }
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
    m=read();
    for(int i=1;i<=n;i++){
        r[i]=read();
    }
    for (int i = 1; i <= n; i++) {
        r[i] = (r[i] % m + m) % m;
    }
    write(excrt(n));
    cout<<endl;
    for(int i=1;i<=n;i++){
        write(res[i]);
        cout<<' ';
    }
    return 0;
}

