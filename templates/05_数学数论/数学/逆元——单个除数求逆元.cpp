// 单个除数求逆元
//可以采用费马小定理  一个数字在%mod的情况下的逆元 就是这个数字的mod-2次方  对mod取余的结果
// 对数器验证
#include<bits/stdc++.h>
using namespace std;

//乘法快速幂  求a的b次方对mod取余
long long power(long long a,long long b,long long mod){
    long long ans=1;
    while(b){
        if(b&1){
            ans*=a;
            ans%=mod;
        }
        b>>=1;
        a*=a;
        a%=mod;
    }
    return ans;
}

//费马小定理求(a/b)%mod的值
long long compute2(long long a,long long b,long long mod){
    long long inv=power(b,mod-2,mod);//求b在%mod的情况下的逆元
    return (a*inv)%mod;
}

//对数器
long long compute1(long long a,long long b,long long mod){
    return (a/b)%mod;
}

int main()
{
    long long a,b,mod;
    cin>>a>>b>>mod;
    // 1) 必须保证a/b可以整除
    // 2) 必须保证mod是质数
    // 3) 必须保证b和mod的最大公约数为1
    cout<<"对数器验证： "<<compute1(a,b,mod)<<endl;
    cout<<"费马小定理： "<<compute2(a,b,mod)<<endl;
    return 0;
}
/*
247143614256
3671613
41
*/