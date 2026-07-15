#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

typedef long long ll;

const int MAX_PRIME = 79;
const ll N_LIMIT = 1e18; // 假设 n 的上限，用于确保处理范围内的数
vector<ll> primes = {0,2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
353, 359, 367, 373, 379, 383, 389, 397
};

struct Node {
    ll value;
    ll prime;
    ll power;
    int limit; // 下一个质数的索引限制

    bool operator<(const Node& other) const {
        return value < other.value;
    }
};

priority_queue<Node> pq;

ll read() {
    ll ret = 0, sign = 1;
    char ch;
    while ((ch = getchar()) < '0' || ch > '9') {
        if (ch == '-') sign = -1;
    }
    while (ch >= '0' && ch <= '9') {
        ret = ret * 10 + (ch - '0');
        ch = getchar();
    }
    return ret * sign;
}

void write(ll x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

void writeln(ll x) {
    write(x);
    putchar('\n');
}

int main() {
    ll n, k;
    n = read();
    k = read();

    // 初始化优先队列
    for (int i = 1; i <= MAX_PRIME; ++i) {
        ll now = primes[i];
        for (int j = 1; now <= n; ++j, now *= primes[i]) {
            pq.push({now, primes[i], j, i - 1});
        }
    }

    // 取出前 k 大的数
    while (k--) {
        Node top = pq.top();
        pq.pop();
        if (k == 0) {
            writeln(top.value);
            break;
        }
        if (top.power > 1) {
            for (int i = max(1,top.limit-10); i <= top.limit; ++i) {
                pq.push({top.value / top.prime * primes[i], top.prime, top.power - 1, i});
            }
        }
    }

    return 0;
}


