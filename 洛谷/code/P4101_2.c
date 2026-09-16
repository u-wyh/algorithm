#include<stdio.h>

int T;
long long int n, m;

int main() {
    scanf("%d", &T);
    for(int i = 1; i <= T; i++) {
        scanf("%lld%lld", &n, &m);
        long long int ans = (n / m) * (m - 1) + ((n % m) ? (n % m - 1) : 0);
        if(ans & 1) {
            printf("0\n");
        } else {
            printf("1\n");
        }
    }
    return 0;
}
