#include <iostream>
using namespace std;
string s,t;
int T, n;
int g[45][22], mask[22];
bool f[45][1 << 21];

int calc (int s, int t) {
    if (s == 0) return 0;
    for (int i = 1; i <= 2 * n; i ++) {
        int vis = s;
        for (int j = 0; j < n; j ++) if (t & (1 << j) ) vis = vis ^ g[i][j];
        if (f[i][vis]) return i;
    }
}

int main() {
    f[0][0] = 1;
    cin >> T >> n;
    for (int i = 0; i <= n; i ++) mask[i] = 1 << i;
    int N = 1 << n;
    for (int k = 0; k < n; k ++)
        for (int i = 1; i <= 2 * n; i ++)
            for (int j = 0; j < i; j ++) g[i][k] ^= mask[(k + j) % n];
    for (int i = 1; i <= 2 * n; i ++) for (int j = 0; j < N; j ++) {
            if (!f[i - 1][j]) continue;
            for (int k = 0; k < n; k ++){
                int vis = j;
                vis ^= g[i][k];
                f[i][vis] = 1;
            }
        }
    while (T --){
        cin >> s >> t;
        int S = 0, T = 0;
        for (int i = 0; i < n; i ++) {
            if (s[i] == '1') S ^= (1 << i);
            if (t[i] == '1') T ^= (1 << i);
        }
        cout << calc(S, T) << "\n";
    }
    return 0;
}