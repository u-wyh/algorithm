#include<bits/stdc++.h>
using namespace std;
#define int long long

int mod,a,b,x,t;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

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

long long d, xx, y, px, py;

void exgcd(long long a, long long b) {
    if (b == 0) {
        //表示已经求出了最大公约数d      x y分别是1 0
        d = a;//最大公约数设置为a
        xx = 1;
        y = 0;
    } else {
        exgcd(b, a % b);
        px = xx;
        py = y;
        xx = py;
        y = px - py * (a / b);
    }
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>mod>>a>>b>>x>>t;
        if(x==t){
            cout<<1<<endl;
            continue;
        }
        if(a==0){
            if(t==b){
                cout<<2<<endl;
            }
            else{
                cout<<-1<<endl;
            }
            continue;
        }
        if(a==1){
            exgcd(b,mod);
            t=(t-x)%mod;
            if(t%d){
                cout<<-1<<endl;
            }
            else{
                int p=(mod/d);
                xx=(xx%p+p)%p;
                xx=(xx*(t/d))%p;
                cout<<xx<<endl;
            }
            continue;
        }
        b=(b*power(a-1,mod-2,mod))%mod;
        t=(t+b)%mod;
        x=(x-b)%mod;
        t=(t*power(x,mod-2,mod))%mod;
        int ans=bsgs(a,t,mod);
        if(ans!=-1){
            ans+=1;
        }
        printf("%lld\n",ans);
    }
    return 0;
}