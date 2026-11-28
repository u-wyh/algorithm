// https://atcoder.jp/contests/fps-24/tasks/fps_24_f
// 题意：给 N 张有编号的纸，每张染成红、蓝或黄。
// 要求蓝纸数为偶数，黄纸数为奇数。
// 输出：合法染色方案数对 998244353 取模。
// 数据范围：1 <= N <= 10^9。
// 难度评分：1600（估算）
// 算法标签：快速幂、组合计数
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

signed main()
{
    int n;
    cin>>n;
    int ans=(n&1)?1:-1;
    ans+=power(3,n);
    ans*=power(4,MOD-2);
    ans%=MOD;
    cout<<ans<<endl;
    return 0;
}