// 用途：求 a 在模 b 下的乘法逆元。
// 时间：O(log b)。
// 空间：递归栈 O(log b)。
// 注意：b>0 且 gcd(a,b)=1 才存在；否则输出 -1。
// 例题：https://www.luogu.com.cn/problem/P1082
// 题意：求 a 在模 b 下的逆元。
// 思路：扩展欧几里得求 ax+by=gcd(a,b)，互质时取 x 的模值。
#include<bits/stdc++.h>
using namespace std;

long long x,y,d,px,py;

// 递归回代求 x、y，使 ax+by=gcd(a,b)。
void exgcd(long long a,long long b){
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
    long long a,b;
    cin>>a>>b;
    if(b<=0){
        cout<<-1<<endl;
        return 0;
    }
    a%=b;
    if(a<0) a+=b;
    exgcd(a,b);
    if(d!=1) cout<<-1<<endl;
    else cout<<(x%b+b)%b<<endl;
    return 0;
}
