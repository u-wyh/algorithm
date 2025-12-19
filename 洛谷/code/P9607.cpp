#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 10;
const int MAXM = 25;  // log n
const int M = 20;
const int MAXK = 35;  // log V
const int INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const int mod = 1e9 + 7;

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b, a % b);
}

int n, ans = 0;
int a[MAXN];
int maxl[MAXN][MAXM], maxr[MAXN][MAXM];  // i向左/向右2^k个数的最大值
int gcdl[MAXN][MAXM], gcdr[MAXN][MAXM];  // i向左/向右2^k个数的gcd
map<int, int> mp;

// 存储每个最大公因数的范围及数值
struct Node {
    int ql, qr, val;
} L[MAXK], R[MAXK];
int cntl, cntr;  // 左右两侧不同gcd值的个数（<logV）

void work(int x) {
    int l = x, r = x;
    int lim = mp[a[x]];  // 上一个相同数字的位置（没有则为0）
    
    // 倍增确定左右边界（满足区间最大值<=a[x]）
    for (int i = M; i >= 0; i--) {
        if (l - (1 << i) > lim && maxl[l - 1][i] <= a[x]) {
            l -= (1 << i);
        }
        if (r + (1 << i) <= n && maxr[r + 1][i] <= a[x]) {
            r += (1 << i);
        }
    }
    
    cntl = 0;
    cntr = 0;
    int Gcd = a[x], p = x;  // 当前gcd值，当前位置
    
    // 向左扩展并记录不同gcd的区间
    while (true) {
        int lst = p;
        for (int i = M; i >= 0; i--) {
            if (p - (1 << i) >= l && gcdl[p - 1][i] % Gcd == 0) {
                p -= (1 << i);
            }
        }
        cntl++;
        L[cntl] = {p, lst, Gcd};
        if (p == l) break;
        p--;
        Gcd = gcd(Gcd, a[p]);
    }
    
    Gcd = a[x];
    p = x;
    // 向右扩展并记录不同gcd的区间
    while (true) {
        int lst = p;
        for (int i = M; i >= 0; i--) {
            if (p + (1 << i) <= r && gcdr[p + 1][i] % Gcd == 0) {
                p += (1 << i);
            }
        }
        cntr++;
        R[cntr] = {lst, p, Gcd};
        if (p == r) break;
        p++;
        Gcd = gcd(Gcd, a[p]);
    }
    
    int res = 0;
    // 枚举左右区间组合，计算贡献
    for (int i = 1; i <= cntl; i++) {
        int lst = L[i].val;
        for (int j = 1; j <= cntr; j++) {
            int lenl = L[i].qr - L[i].ql + 1;
            int lenr = R[j].qr - R[j].ql + 1;
            res = (res + 1LL * lenl * lenr % mod * gcd(lst, R[j].val)) % mod;
        }
    }
    ans = (ans + 1LL * res * a[x]) % mod;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        maxl[i][0] = maxr[i][0] = a[i];
        gcdl[i][0] = gcdr[i][0] = a[i];
    }
    
    // 预处理ST表
    for (int i = 1; i <= M; i++) {
        int len = (1 << (i - 1));
        for (int j = 1; j <= n; j++) {
            maxl[j][i] = maxl[j][i - 1];
            maxr[j][i] = maxr[j][i - 1];
            gcdl[j][i] = gcdl[j][i - 1];
            gcdr[j][i] = gcdr[j][i - 1];
        }
        for (int j = 1; j + len <= n; j++) {
            maxr[j][i] = max(maxr[j][i], maxr[j + len][i - 1]);
            gcdr[j][i] = gcd(gcdr[j][i], gcdr[j + len][i - 1]);
        }
        for (int j = len + 1; j <= n; j++) {
            maxl[j][i] = max(maxl[j][i], maxl[j - len][i - 1]);
            gcdl[j][i] = gcd(gcdl[j][i], gcdl[j - len][i - 1]);
        }
    }
    
    for (int i = 1; i <= n; i++) {
        work(i);
        mp[a[i]] = i;  // 记录数字最后出现位置
    }
    
    printf("%d\n", ans);
    return 0;
}