// https://www.luogu.com.cn/problem/P3846
//这个算法主要求的是  在给出a b mod 情况下  求出满足a^x=b(%mod)的最小的x
//我们可以知道  如果有解的话 那么这个值一定是在0~mod-1之间的  这应该是群论的知识
//但是我们无法枚举mod  因为他可能特别大
//bsgs是一种分块思想  t=根号mod向上取整  令x=A*t+B  A、B取值为0~t
//那么原来的式子就变成 求  a的A*t次方=b*(a的B次方)在%mod的情况下相等
//那么枚举B来枚举右边式子的取值  记录在map中
//然后从小到大枚举A  遇到相等的立即结束  表示找到了答案
#include<bits/stdc++.h>
using namespace std;
#define int long long

int p, b, n;

int power(int a, int b) {
    int ans = 1;
    while (b) {
        if (b & 1) 
            ans = (ans * a) % p;
        a = (a * a) % p;
        b >>= 1;
    }
    return ans;
}

int bsgs(int g, int h, int mod) {
    // 处理特殊情况
    h%=mod;
    g%=mod;

    if(g==0){
        if (h == 0) return 1;  // 0^1 = 0 (x=1)
        if (h == 1) return 0;  // 0^0 = 1 (x=0)
        return -1;             // 无解
    }

    if (h == 1 ) return 0;
    if (h == 0 ) return -1;  // h=0 无解
    
    int t = ceil(sqrt(mod));
    map<int, int> mp;
    int base = h; 
    
    // 小步：存储 h * g^j (j=0 到 t-1)
    for (int j = 0; j < t; j++) {
        mp[base] = j;  // 直接覆盖，保留最大j
        base = (base * g) % mod;
    }
    
    // 计算大步参数
    int tmp = power(g, t);  // g^t
    int cur = 1;  // 当前大步值 (g^{i*t})
    
    // 大步：i 从 0 到 t
    for (int i = 0; i <= t; i++) {
        if (mp.find(cur) != mp.end()) {
            int x = i * t - mp[cur];
            // 调整解到[0, mod-2]范围内
            //费马小定理：a^(p−1)≡1(modp)(对于任意 a!≡0)
            //这意味着指数x在模(p−1)意义下具有周期性：
            //y^x≡y^(x%(p−1))(mod p)
            x = (x % (mod-1) + (mod-1)) % (mod-1);
            return x;
        }
        cur = (cur * tmp) % mod;  // 下一个大步
    }
    return -1;
}

signed main() {
    cin >> p >> b >> n;
    int ans = bsgs(b, n, p);
    if (ans == -1) cout << "no solution";
    else cout << ans;
    return 0;
}