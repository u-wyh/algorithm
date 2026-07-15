#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MOD 998244353

// 检查是否为质数
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// 计算数位和
int digitSum(long long n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int main() {
    long long L, R;
    scanf("%lld %lld", &L, &R);
    long long result = 0;

    // 生成并检查完全平方数
    for (long long i = (long long)ceil(sqrt(L)); i * i <= R; i++) {
        long long square = i * i;
        if (isPrime(digitSum(square))) {
            if(result ==0)
                result =1;
            result = ((result%MOD) * (square% MOD))%MOD;
        }
    }

    printf("%lld\n", result);
    return 0;
}
