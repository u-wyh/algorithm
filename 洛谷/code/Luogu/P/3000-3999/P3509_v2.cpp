#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define dbg(x) cout << #x " = " << (x) << endl
#define quickio ios::sync_with_stdio(false);
#define quickin cin.tie(0);
#define quickout cout.tie(0);
#define maxn 80005
using namespace std;
inline int read() {
    int now = 0, nev = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') nev = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { now = (now << 1) + (now << 3) + (c & 15); c = getchar(); }
    return now * nev;
}
void write(int x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
int n, m, a[maxn], lis[maxn];
int k, pos[maxn], ans[maxn];
signed main() {
    quickio
    quickin
    quickout
    n = read(), k = read(), m = read();
    for(int i = 1; i <= n; i++)
        a[i] = read();
    lis[1] = k + 1; int s = 1, l = k + 1;
    for(int i = 2; i <= n; i++) {
        while(l + 1 <= n && a[i] - a[s] > a[l + 1] - a[i]) s++, l++;
        if(a[i] - a[s] >= a[l] - a[i]) lis[i] = s;
        else lis[i] = l;
    }
    for(int i = 1; i <= n; i++)
        ans[i] = i;
    while(m != 0) {
        if(m & 1) for(int i = 1; i <= n; i++)
            ans[i] = lis[ans[i]];
        for(int i = 1; i <= n; i++)
            pos[i] = lis[i];
        for(int i = 1; i <= n; i++)
            lis[i] = pos[pos[i]];
        m >>= 1;
    }
    for(int i = 1; i <= n; i++)
        write(ans[i]), putchar(' ');
    return 0;
}
