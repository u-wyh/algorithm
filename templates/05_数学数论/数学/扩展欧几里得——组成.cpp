// 无法组成的最大值
// 一共有a、b两种面值的硬币，a和b一定互质，每种硬币都有无限个
// 返回a和b无法组成的钱数中，最大值是多少
// 题目的输入保证存在最大的无法组成的钱数
// 1 <= a、b <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P3951
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
//这道题真的很需要灵感  gcd(a,b)=1
//那么也就是说 ax+by 所可以到达的最小正整数是 1 
//即  ax+by  可以组成任何数字
//但是我们要求x y必须要都大于等于0  
//那么 最终的答案一定是a或者b的系数为-1
//因为如果  -2*a+b*y  是最大无法组成的数字  那么-1*a+b*y要更大  而且更符合要求
//最终可以得到答案是  -a+(a-1)*b=-b+(b-1)*a=ab-a-b
#include<bits/stdc++.h>
using namespace std;

int main()
{
    long long a,b;
    cin>>a>>b;
    cout<<(a*b-a-b);
    return 0;
}