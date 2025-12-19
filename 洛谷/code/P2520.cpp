#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
    if (b == 0) 
        return llabs(a);
    return gcd(llabs(b), llabs(a) % llabs(b));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        ll a, b, x, y;
        cin >> a >> b >> x >> y;

        if (a == 0 && b == 0) {
            if (x == 0 && y == 0) {
                cout << "Y\n";
            } else {
                cout << "N\n";
            }
        } else if (a == 0) {
            if (x % b == 0 && y % b == 0) {
                cout << "Y\n";
            } else {
                cout << "N\n";
            }
        } else if (b == 0) {
            if (x % a == 0 && y % a == 0) {
                cout << "Y\n";
            } else {
                cout << "N\n";
            }
        } else if (llabs(a) == llabs(b)) {
            ll g = llabs(a);
            if (x % g != 0 || y % g != 0) {
                cout << "N\n";
            } else {
                ll x0 = x / g;
                ll y0 = y / g;
                if (((x0 + y0) % 2 == 0) && ((x0 - y0) % 2 == 0)) {
                    cout << "Y\n";
                } else {
                    cout << "N\n";
                }
            }
        } else {
            ll g = gcd(a, b);
            ll a1 = a / g;
            ll b1 = b / g;
            ll g1 = g * g;
            if ((llabs(a1) % 2 == 1) && (llabs(b1) % 2 == 1)) {
                g1 *= 2;
            }
            ll R = (ll)b * y - (ll)a * x;
            if (R % g1 == 0) {
                cout << "Y\n";
            } else {
                cout << "N\n";
            }
        }
    }
    return 0;
}