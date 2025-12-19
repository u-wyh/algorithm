#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1010;
int n, m, t, maxn, maxc, f[N][N];
pair<int, int> a[N];

int main() {
    cin >> n >> m >> t;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    memset(f, -0x3f, sizeof(f));
    f[0][0] = maxn = m;
    for (int i = 0; i <= t; i++) {
        for (int j = 0; j <= t; j++) {
            for (int k = 1; k <= n; k++) {
                if (a[k].second + maxc >= t && maxn >= a[k].first) {
                    cout << i + 1;
                    return 0;
                }
                if (j - a[k].second >= 0 && f[i][j - a[k].second] - a[k].first >= 0) {
                    f[i][j] = max(f[i][j], f[i][j - a[k].second] - a[k].first);
                }
            }
            if (f[i][j] >= t) {
                cout << i;
                return 0;
            }
            if (f[i][j] > maxn) {
                maxn = f[i][j];
                maxc = j;
            }
            f[i + 1][j] = f[i][j] + j;
        }
    }
    return 0;
}
