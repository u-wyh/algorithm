//用于判断一个很大的数字是否是一个质数
// Miller-Rabin测试，java版，不用BigInteger也能通过的实现
// 这个文件课上没有讲，课上讲的是，java中的long是64位
// 所以 long * long 需要128位才能不溢出，于是直接用BigInteger中自带的方法了
// 但是
// 如果a和b都是long类型，其实 a * b 的过程，用位运算去实现，中间结果都 % mod 即可
// 这样就不需要使用BigInteger
// 讲解033，位运算实现乘法，增加 每一步 % mod 的逻辑即可
// 重点看一下本文件中的 multiply 方法，就是位运算实现乘法的改写
// C++的同学也可以用这种方式来实现，也不需要定义128位的long类型
// 测试链接 : https://www.luogu.com.cn/problem/U148828
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define MAX_TESTS 10

// 快速幂函数，计算 (base^exp) % mod
int64_t qpow(int64_t base, int64_t exp, int64_t mod) {
    int64_t result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// Miller-Rabin素数测试
bool miller_rabin(int64_t n, int s) {
    if (n < 3 || n % 2 == 0) return n == 2;

    int64_t u = n - 1, t = 0;
    while (u % 2 == 0) {
        u /= 2;
        t++;
    }

    int64_t primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (int i = 0; i < s && primes[i] < n; i++) {
        int64_t a = primes[i];
        if (n % a == 0) return false;

        int64_t x = qpow(a, u, n);
        if (x == 1 || x == n - 1) continue;

        for (int j = 1; j < t; j++) {
            x = (x * x) % n;
            if (x == n - 1) break;
        }

        if (x != n - 1) return false;
    }

    return true;
}

int main() {
    int t;
    scanf("%d", &t);

    char buffer[100]; // 假设数字不会太长，足以用字符串读取
    while (t--) {
        scanf("%s", buffer);
        int64_t n = strtoll(buffer, NULL, 10);

        if (miller_rabin(n, MAX_TESTS)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}