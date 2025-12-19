// 连续数字逆元的线性递推
// 给定n、p，求1∼n中所有整数在模p意义下的乘法逆元
// 1 <= n <= 3 * 10^6
// n < p < 20000528
// 输入保证p为质数
// 测试链接 : https://www.luogu.com.cn/problem/P3811
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e6+5;

int n,mod;//求数字 1~n  在%mod意义下的逆元
int inv[MAXN];//逆元表

// 预计算模逆元
void build(int n) {
    inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        inv[i] = (mod - (long long)inv[mod % i] * (mod / i) % mod + mod) % mod;
    }
}

int main()
{
    scanf("%d %d", &n, &mod);
    build(n);
    for (int i = 1; i <= n; i++) {
        printf("%d\n", inv[i]);
    }
    return 0;
}