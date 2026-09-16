// 范围内的数字计数
// 给定两个正整数a和b，求在[a,b]范围上的所有整数中
// 每个数码(digit)各出现了多少次
// 1 <= a, b
// 测试链接 : https://www.luogu.com.cn/problem/P2602
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
#include<bits/stdc++.h>
using namespace std;

long a,b;

long count(long num, int d) {
    long ans = 0;
    for (long right = 1, tmp = num, left, cur; tmp != 0; right *= 10, tmp /= 10) {
        //我们目前统计的是这一位上的d对答案的贡献  我们分为两个部分来求
        //第一个部分是 前面的数字严格小于真实的部分 也就是left  可以取值0~left-1  因为后面数字可以随便取  如果前面填了left 可能会导致数字过大
        //第二个部分是 前面的数字就是left  查看这个位置还能贡献多少的答案  此时取决于后面right
        left = tmp / 10;
        if (d == 0) {
            //如果d=0的话  那么前面不能是0  否则没有统计意义
            left--;
        }
        ans += left * right;
        cur = tmp % 10;
        //统计第二部分答案
        if (cur > d) {
            //当前位上值大于d  那么后面的可以随便填
            ans += right;
        } else if (cur == d) {
            //如果恰好相等  那么后面可以填的就是  0~后面真实的数字  即真实值+1
            ans += num % right + 1;
        }
    }
    return ans;
}

int main()
{
    cin>>a>>b;
    for(int d=0;d<10;d++){
        cout<<(count(b,d)-count(a-1,d))<<' ';
    }
    return 0;
}