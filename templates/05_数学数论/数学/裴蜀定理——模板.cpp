// 裴蜀定理模版题
// 给定长度为n的一组整数值[a1, a2, a3...]，你找到一组数值[x1, x2, x3...]
// 要让a1*x1 + a2*x2 + a3*x3...得到的结果为最小正整数
// 返回能得到的最小正整数是多少
// 1 <= n <= 20
// 1 <= ai <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P4549
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
//这道题就是裴蜀定理的应用
//A*a+B*b+'''+Z*z  对于固定的A B'''Z而言 任意的整数a b ''' z   所能得到的最小正数就是他们的最大公约数
#include<bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main()
{
    int n;
    cin>>n;
    int ans=0;
    for(int i=1;i<=n;i++){
        int k;
        cin>>k;
        ans=gcd(abs(k),ans);
    }
    cout<<ans<<endl;
    return 0;
}