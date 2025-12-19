#include <iostream>
#include <vector>
#include <cstring>
#include <climits>

using namespace std;

typedef long long i64;
const int INF = INT_MAX;
const int MAXN = 1e5 + 3;

int read() {
    int w = 1, c, ret = 0;
    while ((c = getchar()) > '9' || c < '0') w = (c == '-' ? -1 : 1);
    ret = c - '0';
    while ((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + c - '0';
    return ret * w;
}

int main() {
    int n = read(), q = read();
    vector<int> A(n + 1, 0), B(n + 1, 0), N(n + 1, 0);
    bool found = false;
    int t = 0;

    // Read and process queries
    for (int i = 0; i < q; ++i) {
        int s = read(), t = read();
        if (s < t) {
            ++A[s - 1];
            --A[t - 1];
        } else if (s > t) {
            ++B[t];
            --B[s];
        }
    }

    // Calculate prefix sums
    for (int i = 1; i <= n; ++i) {
        A[i] += A[i - 1];
        B[i] += B[i - 1];
    }
    // Check if there's any overlap
    for (int i = 1; i <= n - 2; ++i) {
        if (A[i] && B[i]) {
            found = true;
            break;
        }
    }

    if (found) {
        cout << "QED" << endl;
        return 0;
    }
    // Assign numbers
    for (int i = 1; i <= n; ++i) {
        if (!N[i]) {
            int count = 1;
            for (int j = i; A[j] && j + 2 <= n; j += 2) {
                ++count;
            }
            for (int j = 1; j <= count; ++j) {
                N[i + 2 * count - 2 * j] = ++t;
            }
        }
    }
    // Print result
    for (int i = 1; i <= n; ++i) {
        cout << N[i];
        if (i != n) {
            cout << " ";
        } else {
            cout << endl;
        }
    }

    return 0;
}
