// https://www.luogu.com.cn/problem/P1226
// 题意：给出底数 a、指数 b 和模数 p，求 a 的 b 次方除以 p 的余数 s。
// 输出格式为 a^b mod p=s，把 a、b、p、s 换成相应的数值。
// 数据范围：0 ≤ a, b < 2^31，a + b > 0，2 ≤ p < 2^31。
// 算法标签：快速幂

#include <stdio.h>

long a, b, p,A,B;

long power() {
    long ans = 1;
    while (b > 0) {
        if (b & 1) {
            ans = (ans * a) % p;
        }
        a = (a * a) % p;
        b >>= 1;
    }
    return ans;
}

int main() {
    scanf("%ld %ld %ld", &a, &b, &p);
    A=a;
    B=b;
    printf("%ld^%ld mod %ld=%ld\n", A, B, p, power());
    return 0;
}
