#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
int n, m, r, c, q;
int qread(){
    int w=1,c,ret;
    while((c = getchar()) >  '9' || c <  '0') w = (c == '-' ? -1 : 1); ret = c - '0';
    while((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + c - '0';
    return ret * w;
}
const int MAXN = 2e3 + 3;
const int MAXM =  50 + 3;
const int MOD  = 998244353;
int A[MAXN][MAXN], S[MAXN][MAXN]; bool B[MAXN][MAXN];
int calc(int a1, int b1, int a2, int b2){
    int ret = S[a2][b2];
    if(a1 > r) ret = (ret - S[a1 - r][b2] + MOD) % MOD;
    if(b1 > c) ret = (ret - S[a2][b1 - c] + MOD) % MOD;
    if(a1 > r && b1 > c) ret = (ret + S[a1 - r][b1 - c]) % MOD;
    return ret;
}
int main(){
    n = qread(), m = qread();
    up(1, n, i) up(1, m, j) A[i][j] = qread();
    r = qread(), c = qread();
    up(1, r, i) up(1, c, j) B[i][j] = qread();
    up(1, n, i) up(1, m, j){
        S[i][j] = A[i][j];
        if(i > r) S[i][j] = (S[i][j] + S[i - r][j]) % MOD;
        if(j > c) S[i][j] = (S[i][j] + S[i][j - c]) % MOD;
        if(i > r && j > c)
            S[i][j] = (S[i][j] - S[i - r][j - c] + MOD) % MOD;
    }
    q = qread();
    up(1, q, i){
        int _x1 = qread(), _y1 = qread();
        int _x2 = qread(), _y2 = qread();
        int ans = 0;
        up(1, min(r, _x2 - _x1 + 1), a)
            up(1, min(c, _y2 - _y1 + 1), b) if(B[a][b] == 0){
                int a1 = _x1 + a - 1, a2 = a1 + (_x2 - a1) / r * r;
                int b1 = _y1 + b - 1, b2 = b1 + (_y2 - b1) / c * c;
                ans = (ans + calc(a1, b1, a2, b2)) % MOD;
        }
        printf("%d\n", ans);
    }

    return 0;
}
