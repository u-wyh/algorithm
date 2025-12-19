#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long ll;

vector<ll> sieve_small_primes(ll n) {
    if (n < 2) 
        return vector<ll>();
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= n; ++i) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    vector<ll> primes;
    for (ll i = 2; i <= n; ++i) {
        if (is_prime[i])
            primes.push_back(i);
    }
    return primes;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n, p;
    cin >> n >> p;

    if (n == 1) {
        cout << 1 % p << endl;
        return 0;
    }

    ll sqrt_n = sqrt(n);
    vector<ll> small_primes = sieve_small_primes(sqrt_n);

    ll ans1 = 1;
    for (ll q : small_primes) {
        ll power = q;
        while (power <= n / q) {
            power *= q;
        }
        ans1 = (ans1 * power) % p;
    }

    ll L = sqrt_n + 1;
    ll R = n;
    ll ans2 = 1;

    if (L <= R) {
        if (L % 2 == 0) {
            L++;
        }
        if (L > R) {
            // Do nothing
        } else {
            const ll SEG_SIZE = 1 << 16;
            for (ll low_seg = L; low_seg <= R; low_seg += 2 * SEG_SIZE) {
                ll high_seg = min(low_seg + 2 * (SEG_SIZE - 1), R);
                ll num_odds = ((high_seg - low_seg) >> 1) + 1;
                vector<bool> sieve(num_odds, true);

                for (ll q : small_primes) {
                    if (q == 2) continue;
                    ll start = (low_seg + q - 1) / q * q;
                    if (start < low_seg) start += q;
                    if (start % 2 == 0) start += q;
                    if (start > high_seg) continue;

                    ll start_index = (start - low_seg) >> 1;
                    for (ll idx = start_index; idx < num_odds; idx += q) {
                        sieve[idx] = false;
                    }
                }

                for (ll i = 0; i < num_odds; ++i) {
                    if (sieve[i]) {
                        ll prime = low_seg + 2 * i;
                        if (prime > R) break;
                        ans2 = (ans2 * prime) % p;
                    }
                }
            }
        }
    }

    ll ans = (ans1 * ans2) % p;
    cout << ans << endl;

    return 0;
}