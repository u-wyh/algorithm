// https://www.luogu.com.cn/problem/P5091
// 扩展欧拉定理
// 用途：
// 求 a^b mod m
// 当指数 b 非常大，甚至无法使用 long long 保存时
// 可以利用欧拉函数对指数进行降幂
//
// 普通欧拉定理：
// gcd(a,m)=1 时：
// a^phi(m) ≡ 1 (mod m)
//
// 扩展欧拉降幂：
//
// 如果 b < phi(m)：  指数仍然使用 b
// 如果 b >= phi(m)： 指数可以变成  b % phi(m) + phi(m)
// 即：
// a^b ≡ a^(b%phi(m)+phi(m)) (mod m)
//
// 这个写法可以统一处理 gcd(a,m)=1 和 gcd(a,m)!=1
//
// 注意：
// 不能无脑只使用 b%phi(m)
// 当 gcd(a,m)!=1 时，把指数降得太小可能导致错误
// 也不能无脑给 b%phi(m) 加上 phi(m)
// 当 gcd(a,m)!=1 且 b<phi(m) 时会出错
#include<bits/stdc++.h>
using namespace std;
#define int long long

int phi(int n){
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