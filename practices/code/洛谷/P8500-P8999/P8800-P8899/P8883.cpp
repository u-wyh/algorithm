// https://www.luogu.com.cn/problem/P8883
// 题意：T 组询问，每组输入正整数 n，
// 输出 1..n 中能被大于 1
// 的完全平方数整除的整数个数（允许答案与标准答案的绝对误差不超过 2*10^4）。
// 数据范围：1 <= n <= 10^18，
// 1 <= T <= 10^4（保证 n 在范围内随机生成）。
// 难度评分：1900（洛谷分级换算）
// 算法标签：数学
#include<bits/stdc++.h>
using namespace std;
#define int long long
const long double pi = 3.141592653589793238462643383279;

signed main()
{
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        cout<<(long long)(n*(1.0-6.0/(pi*pi)))<<endl;
    }
    return 0;
}