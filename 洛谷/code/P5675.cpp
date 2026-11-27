// https://www.luogu.com.cn/problem/P5675
// 题意：有 N 堆石子，你选出若干堆石子做 Nim 游戏并指定 Alice 第一次必须从其中哪一堆取（只要包含该堆且选法或指定堆不同即算不同方案）
// 求让 Alice 必败的方案数。
// 输入 N 及每堆石子数；输出方案数模 10^9+7。
// 数据范围：1 <= N <= 200，每堆石子数量 <= 200。
// 算法标签：动态规划、博弈论、位运算
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 205;

int n;
int arr[MAXN];
int dp[MAXN][260];

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    int ans=0;
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        //枚举每一个第一个点
        //每次更换枚举点的时候  dp不用初始化  因为每次都是从上一层转移的
        //而0层就是0  不会变
        for(int j=1;j<=n;j++){
            for(int k=0;k<=255;k++){
                if(i==j){
                    dp[j][k]=dp[j-1][k^arr[j]];
                }
                else{
                    dp[j][k]=(dp[j-1][k]+dp[j-1][arr[j]^k])%MOD;
                }
            }
        }
        ans+=dp[n][0];
        ans%=MOD;
        for(int j=arr[i]+1;j<=255;j++){
            ans=(ans+dp[n][j])%MOD;
        }
    }
    cout<<ans<<endl;
    return 0;
}
