// https://www.luogu.com.cn/problem/P1450
// 题意：有四种面值固定的硬币。每次购物给出四种硬币各自可用的上限 d 和目标金额 s。统计从各类硬币选若干枚，正好付出 s 的不同数量组合。
// 数据范围：1 ≤ c[i],d[i],s ≤ 10^5，1 ≤ n ≤ 1000 次购物。
// 算法标签：背包动态规划、容斥原理

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

long long dp[MAXN];
int c[5],d[5];

int main()
{
    for(int i=1;i<=4;i++){
        cin>>c[i];
    }
    dp[0]=1;
    for(int i=1;i<=4;i++){
        for(int j=c[i];j<=MAXN;j++){
            dp[j]+=dp[j-c[i]];
        }
    }
    int T;
    cin>>T;
    while(T--){
        for(int i=1;i<=4;i++){
            cin>>d[i];
        }
        int sum;
        cin>>sum;
        long long ans=0;
        for(int i=0;i<16;i++){
            long long t=sum;
            int cnt=0;
            for (int j = 1; j <= 4; j++) {
                if ((i >> (j - 1)) & 1) {
                    t -= c[j] * (d[j] + 1);
                    cnt ^= 1;
                }
            }

            if (t < 0) continue;

            if (!cnt) {
                ans += dp[t];
            } else {
                ans -= dp[t];
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
