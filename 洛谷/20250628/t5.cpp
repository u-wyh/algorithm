#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        vector<int> b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }

        vector<int> d(n);
        for (int i = 0; i < n; i++) {
            d[i] = (a[i] - b[i]) % m;
            if (d[i] < 0) {
                d[i] += m;
            }
        }
        sort(d.begin(), d.end());
        int gap = d[0] + m - d[n-1];
        for (int i = 0; i < n-1; i++) {
            gap = max(gap, d[i+1] - d[i]);
        }
        cout << m - gap << '\n';
    }

    return 0;
}