#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int min(int a,int b){
    return a<b?a:b;
}

int main() {
    int t, n, a, b, c, d, e;
    ll ans1, ans2;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d %d %d %d", &n, &a, &b, &c, &d, &e);

        if (d >= n - 1) {
            ans1 = (ll)(n - 1) * a + ((d - n + 1 > e) ? a : ((d - n + 1 == e) ? c : b));

            if (d - n + 1 < e && d >= e) {
                ans1 = (ans1 > (c + (ll)(d - e) * a + (ll)(n - 1 - d + e) * c)) ? ans1 : (c + (ll)(d - e) * a + (ll)(n - 1 - d + e) * c );
            }
        } else {
            ans1 = (ll)d * a + (ll)(n - d - 1) * c + b;
            if (e <= d) {
                ans1 = (ans1 > ((ll)e * c + (ll)(d - e) * a + (ll)(n - d) * c)) ? ans1 : ((ll)e * c + (ll)(d - e) * a + (ll)(n - d) * c);
            }
        }

        if (e >= n - 1) {
            ans2 = (ll)(n - 1) * b + ((e - n + 1 > d) ? b : ((e - n + 1 == d) ? c : a));
            if (e - n + 1 < d && e >= d) {
                ans2 = (ans2 < (c + (ll)min(e - d, n - 1) * b + ((e - d < n - 1) ? (ll)(n - 1 - e + d) * c : 0))) ? ans2 : (c + (ll)min(e - d, n - 1) * b + ((e - d < n - 1) ? (ll)(n - 1 - e + d) * c : 0));
            }
        } else {
            ans2 = (ll)e * b + (ll)(n - e - 1) * c + a;
            if (d <= e) {
                ans2 = (ans2 < ((ll)d * c + (ll)(e - d) * b + (ll)(n - e) * c)) ? ans2 : ((ll)d * c + (ll)(e - d) * b + (ll)(n - e) * c);
            }
        }

        printf("%lld %lld\n", ans1, ans2);
    }
    return 0;
}
