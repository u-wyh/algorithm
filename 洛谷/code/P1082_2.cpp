// https://www.luogu.com.cn/problem/P1082
// 扩展欧几里得 exgcd 解 ax + by = gcd(a,b)，常用于：
// 1) 求模逆元：ax ≡ 1 (mod m) 等价于 ax + my = 1，当 gcd(a,m)=1 时 x 即 a^{-1} mod m；
// 2) 解线性同余：ax ≡ b (mod m)，先判断 gcd(a,m)|b，再求特解与通解；
// 3) 解二元一次不定方程：ax + by = c；
// 4) CRT / 扩展 CRT 合并同余方程；
// 为什么求逆元用 exgcd 而不是费马小定理？
// 费马小定理只适用于模数 p 是质数，即 a^{-1} ≡ a^{p-2} (mod p)；
// 欧拉定理虽推广到 gcd(a,m)=1，但需要知道 φ(m)，大合数下很难求。
// exgcd 只要求 gcd(a,m)=1，不要求模数是质数，且 gcd≠1 时能直接判断逆元不存在，
// 所以合数模、RSA、扩展 CRT 等场景必须用它；费马只是质数模下的快速特例。
#include<bits/stdc++.h>
using namespace std;

int x,y,d,px,py;

void exgcd(int a,int b){
    if(b==0){
        d=a;
        x=1;
        y=0;
    }
    else{
        exgcd(b,a%b);
        px=x;
        py=y;
        x=py;
        y=px-py*(a/b);
    }
}

int main()
{
    int a,b;
    cin>>a>>b;
    exgcd(a,b);
    cout<<((x%b)+b)%b<<endl;
    return 0;
}