// https://www.luogu.com.cn/problem/P1412
// 题意：飞船依次经过 n 颗行星，钻头初始能力为 w。
// 资源星可选择开采，赚 a×当前能力，随后能力下降 k%。
// 维修星可选择付款 b×当前能力，随后能力上升 c%。
// 也可跳过，允许透支。
// 求最大净收入，保留两位小数。
// 数据范围：n ≤ 100000，0 ≤ k,c,w,a,b ≤ 100，
// 答案不超过 10^9。
// 算法标签：动态规划

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

double dp[MAXN];
int n,k,c,w;
int op[MAXN],val[MAXN];

int main()
{
    cin>>n>>k>>c>>w;
    for(int i=1;i<=n;i++){
        cin>>op[i]>>val[i];
    }
    for(int i=n;i>=1;i--){
        if(op[i]==1){
            dp[i]=max(dp[i+1],val[i]+dp[i+1]*(1-0.01*k));
        }
        else{
            dp[i]=max(dp[i+1],dp[i+1]*(1+0.01*c)-val[i]);
        }
    }
    cout<<fixed<<setprecision(2)<<(dp[1]*w)<<endl;
    return 0;
}
