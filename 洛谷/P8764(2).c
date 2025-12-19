#include <stdio.h>

typedef long long ll;

// 计算组合（b在下面，a在上面）
ll C(ll b, ll a) {
    ll sum = 1;
    for (ll i = b, j = 1; j <= a; i--, j++) {
        sum = sum * i / j;
    }
    return sum;
}

int main() {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    ll cnt = 0, ans = 0;

    if (n == k && k == 1) {
        ans = 1;
        printf("%lld\n", ans);
        return 0;
    }

    for (int i = 62; i >= 1; --i) {
        if (k - cnt + 1 == 0)
            break;
        if ((1ll << i) & n) {
            cnt++;
            if (i >= k - cnt + 1) {
                //这里统计的是 这一位置上是1的时候  如果强制为0  那么可以有多少种答案
                //并且在此之前位置上是1的 现在还是1
                ans += C(i, k - cnt + 1);
            }
        }
    }

    if (cnt == k)
        ans++;

    printf("%lld\n", ans);
    return 0;
}
