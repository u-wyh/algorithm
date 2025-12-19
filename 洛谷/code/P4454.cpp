#include<bits/stdc++.h>
using namespace std;
#define int long long

int power(int a, int b,int mod) {
    int ans = 1;
    while (b) {
        if (b & 1) 
            ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans;
}

int bsgs(int g, int h, int mod) {
    // 处理特殊情况
    h%=mod;
    g%=mod;

    if(g==0){
        if (h == 0) return 1;  
        if (h == 1) return 0; 
        return -1;           
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
    int tmp = power(g, t,mod);  // g^t
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

signed main()
{
    int g,p,t;
    cin>>g>>p>>t;
    while(t--){
        int A,B;
        cin>>A>>B;
        int a,b;
        a=bsgs(g,A,p);
        b=bsgs(g,B,p);
        int k=power(g,a*b,p);
        cout<<k<<endl;
    }
    return 0;
}