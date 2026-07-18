//https://www.luogu.com.cn/problem/P6091
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

typedef long long ll;
const int MAXN = 1000000; // 最大范围

int phi[MAXN + 10]; // 欧拉函数值
int min_prime[MAXN + 10]; // 最小质因子
bool exist_rt[MAXN + 10]; // 是否存在原根
bool vis[MAXN + 10]; // 筛法标记数组
vector<int> primes; // 素数表

// 快速幂取模：计算 (base^exp) % mod
ll qpow(ll base, ll exp, ll mod) {
    ll res = 1;
    base %= mod; // 确保 base 在模数范围内
    while (exp) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

// 最大公约数（递归实现）
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// 欧拉筛：预处理欧拉函数和最小质因子
void sieve() {
    phi[1] = 1;
    for (int i = 2; i <= MAXN; i++) {
        if (!vis[i]) {
            primes.push_back(i);
            min_prime[i] = i;
            phi[i] = i - 1; // 素数的欧拉函数值为 i-1
        }
        for (size_t j = 0; j < primes.size(); j++) {
            int p = primes[j];
            if (1LL * i * p > MAXN) break;
            vis[i * p] = true;
            min_prime[i * p] = p;
            if (i % p == 0) {
                phi[i * p] = phi[i] * p; // 线性性质
                break;
            } else {
                phi[i * p] = phi[i] * (p - 1); // 积性性质
            }
        }
    }
}

int main() {
    sieve(); // 预处理欧拉函数和最小质因子

    // 标记存在原根的数
    exist_rt[2] = exist_rt[4] = true; // 2 和 4 有原根
    for (size_t i = 0; i < primes.size(); i++) {
        int p = primes[i];
        if (p == 2) continue; // 跳过素数2
        for (ll j = p; j <= MAXN; j *= p) {
            exist_rt[j] = true; // 标记 p^k
            if (j * 2 <= MAXN) exist_rt[j * 2] = true; // 标记 2p^k
        }
    }

    int T;
    cin >> T;
    while (T--) {
        int n_val, d;
        cin >> n_val >> d;
        
        // 处理不存在原根的情况
        if (!exist_rt[n_val]) {
            cout << 0 << endl << endl; // 输出0和空行
            continue;
        }

        // 计算 φ(n) 的质因子分解
        int phi_val = phi[n_val];
        vector<int> fac; // 存储 φ(n) 的质因子
        int temp = phi_val;
        while (temp > 1) {
            int p = min_prime[temp];
            fac.push_back(p);
            while (temp % p == 0) temp /= p; // 移除所有相同因子
        }

        // 寻找最小原根 g
        int g = -1;
        // 枚举 g 从 1 到 min(n_val-1, 200000)
        for (int i = 1; i <= min(n_val - 1, 200000); i++) {
            if (gcd(i, n_val) != 1) continue; // 跳过不互质的数
            
            bool valid = true;
            for (int p : fac) {
                // 检查 g^(φ(n)/p) mod n 是否为1
                if (qpow(i, phi_val / p, n_val) == 1) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                g = i;
                break;
            }
        }
        
        // 未找到原根（理论上应存在）
        if (g == -1) {
            cout << 0 << endl << endl;
            continue;
        }

        // 生成所有原根：g^k mod n_val (gcd(k, φ(n))=1)
        vector<int> all_roots;
        for (int k = 1; k <= phi_val; k++) {
            if (gcd(k, phi_val) == 1) {
                all_roots.push_back(qpow(g, k, n_val));
            }
        }
        sort(all_roots.begin(), all_roots.end()); // 排序
        
        // 输出结果
        int c = all_roots.size();
        cout << c << endl; // 原根总数
        
        // 按间隔 d 输出
        vector<int> output;
        for (int i = d - 1; i < c; i += d) { // 从第 d 个开始取
            output.push_back(all_roots[i]);
        }
        
        if (output.empty()) {
            cout << endl; // 空行
        } else {
            for (size_t i = 0; i < output.size(); i++) {
                if (i) cout << " ";
                cout << output[i];
            }
            cout << endl;
        }
    }
    return 0;
}