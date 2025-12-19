// 树屋阶梯
// 地面高度是0，想搭建一个阶梯，要求每一个台阶上升1的高度，最终到达高度n
// 有无穷多任意规格的矩形材料，但是必须选择n个矩形，希望能搭建出阶梯的样子
// 返回搭建阶梯的不同方法数，答案可能很大，不取模！就打印真实答案
// 1 <= n <= 500
// 测试链接 : https://www.luogu.com.cn/problem/P2532
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> get_primes(int max_n) {
    vector<bool> is_prime(max_n + 1, true);
    vector<int> primes;
    for (int p = 2; p <= max_n; ++p) {
        if (is_prime[p]) {
            primes.push_back(p);
            for (int i = p * 2; i <= max_n; i += p) {
                is_prime[i] = false;
            }
        }
    }
    return primes;
}

int get_exponent(int m, int p) {
    int count = 0;
    while (m > 0) {
        m /= p;
        count += m;
    }
    return count;
}

vector<int> multiply(const vector<int>& a, int b) {
    vector<int> c;
    int carry = 0;
    for (int digit : a) {
        int product = digit * b + carry;
        c.push_back(product % 10);
        carry = product / 10;
    }
    while (carry > 0) {
        c.push_back(carry % 10);
        carry /= 10;
    }
    return c;
}

int main() {
    int n;
    cin >> n;

    int m = 2 * n;

    vector<int> primes = get_primes(m);

    unordered_map<int, int> exponents;
    for (int p : primes) {
        int e1 = get_exponent(m, p);
        int e2 = get_exponent(n, p);
        exponents[p] = e1 - 2 * e2;
    }

    // 处理n+1的分解
    int temp = n + 1;
    for (int p : primes) {
        if (p > temp) break;
        if (temp % p == 0) {
            int cnt = 0;
            while (temp % p == 0) {
                cnt++;
                temp /= p;
            }
            exponents[p] -= cnt;
        }
    }
    if (temp > 1) {
        exponents[temp] -= 1;
    }

    vector<int> result = {1}; // 初始化为1
    for (int p : primes) {
        int e = exponents[p];
        if (e <= 0) continue;
        for (int i = 0; i < e; ++i) {
            result = multiply(result, p);
        }
    }

    for (auto it = result.rbegin(); it != result.rend(); ++it) {
        cout << *it;
    }
    cout << endl;

    return 0;
}