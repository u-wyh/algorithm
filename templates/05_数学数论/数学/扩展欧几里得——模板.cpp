// 同余方程
// 求关于x的同余方程 ax ≡ 1(mod b) 的最小正整数解
// 题目保证一定有解，也就是a和b互质
// 2 <= a、b <= 2 * 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P1082
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
//在exgcd之后 求出来的特解x实际上是a在%b意义下的逆元
#include<bits/stdc++.h>
using namespace std;

long long d, x, y, px, py;

void exgcd(long long a, long long b) {
    if (b == 0) {
        //表示已经求出了最大公约数d      x y分别是1 0
        d = a;//最大公约数设置为a
        x = 1;
        y = 0;
    } else {
        exgcd(b, a % b);
        //这个过程在向上的时候逐步更新
        //d=x'*a'+y'*b'
        // =x'*b+y'*(a-(a/b)*b)
        // =y'*a+(x'-(a/b)*y')b
        // =x*a+y*b
        //x=y'   y=x'-(a/b)*y'
        px = x;
        py = y;
        x = py;
        y = px - py * (a / b);
    }
}

int main()
{
    long long a,b;
    cin>>a>>b;
    exgcd(a,b);
    cout<<((x % b + b) % b);
    return 0;
}