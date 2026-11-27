// https://www.luogu.com.cn/problem/P2092
// 题意：给定正整数 Q，
// 两人轮流将当前数替换为它的一个真因数（不能是 1 和自身）。
// 第一个没有数字可写的人获胜，双方都采取最优策略。
// 第一行输出胜者（先手 1，后手 2）；
// 若先手胜，第二行输出第一步能制胜的最小数字。
// 若先手第一步就无法写出数字，第二行输出 0。
// 数据范围：2 <= Q <= 10^13。
// 算法标签：质因数分解、博弈论
#include<bits/stdc++.h>
using namespace std;

int main()
{
    long long n;
    int cnt=0;
    long long ans=1;
    cin>>n;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
                cnt++;
                //cout<<i<<' ';
                if(cnt<=2){
                    ans*=i;
                }
            }
        }
    }
    if (n > 1) {
        //cout<<n<<endl;
        cnt++;
    }
    //cout<<cnt<<endl;
    if(cnt==2){
        cout<<2<<endl;
        return 0;
    }
    if(cnt==1){
        cout<<1<<endl<<0<<endl;
        return 0;
    }
    cout<<1<<endl;
    cout<<ans<<endl;
    return 0;
}
