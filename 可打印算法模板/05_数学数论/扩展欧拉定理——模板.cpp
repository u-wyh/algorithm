// 用途：指数以十进制大整数给出时，计算 a^b mod m。
// 时间：O(√m+|b|+log m)，|b| 是指数字符串长度。
// 空间：O(|b|)。
// 例题：https://www.luogu.com.cn/problem/P5091
// 题意：指数是十进制大整数，计算 a^b mod m。
// 思路：先求 φ(m)，读入大指数并根据扩展欧拉定理缩减指数。
// 降幂公式：a^b mod m = a^(b mod φ(m)+φ(m)) mod m（b≥φ(m)）；若 b<φ(m)，直接用 b。
// 这样写不要求 gcd(a,m)=1；只有互质时才能无条件直接把指数对 φ(m) 取模。
#include<bits/stdc++.h>
using namespace std;
#define int long long

int phi(int n){
    // 试除分解 m 的不同质因子，计算欧拉函数 φ(m)。
    int ans=n;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            ans=ans/i*(i-1);
            while(n%i==0){
                n/=i;
            }
        }
    }
    if(n>1){
        ans=ans/n*(n-1);
    }
    return ans;
}

int power(int a,int b,int p){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%p;
        }
        b>>=1;
        a=(a*a)%p;
    }
    return ans;
}

signed main()
{
    int a,m;
    string b;
    cin>>a>>m>>b;

    if(m==1){
        cout<<0<<endl;
        return 0;
    }

    int p=phi(m);
    int val=0;
    int num=0;
    bool big=false;

    for(char c:b){
        // val 记录 b mod φ(m)；big 判断 b 是否已达到 φ(m)。
        int x=c-'0';
        val=(val*10+x)%p;
        if(!big){
            num=num*10+x;
            if(num>=p){
                big=true;
            }
        }
    }

    if(big){
        val+=p;
    }
    else{
        val=num;
    }
    cout<<power(a,val,m)<<endl;
    return 0;
}
