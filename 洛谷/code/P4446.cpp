// https://www.luogu.com.cn/problem/P4446
// 题意：给定 n 个正整数 x
// 对每个 x 将三次根式 sqrt[3]{x} 化简为 a * sqrt[3]{b} 的最简形式（即求满足 a^3 * b = x 的最大正整数 a）
// 并输出 a。
// 数据范围：1 <= n <= 10000，1 <= x <= 10^18。
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int T;
    cin>>T;
    while(T--){
        long long n;
        int cnt=0;
        long long ans=1;
        cin>>n;
        for (long long i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                cnt=0;
                while (n % i == 0) {
                    n /= i;
                    cnt++;
                }
                ans*=pow(i,cnt/3);
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
