// https://www.luogu.com.cn/problem/P1356
// 题意：给整数序列和 k，在相邻数字之间任放一个加号或减号，首项照原样。
// 若有一种表达式能被 k 整除，输出 Divisible，否则输出 Not divisible。
// 数据范围：1 ≤ M ≤ 20，1 ≤ n ≤ 10^4，2 ≤ k ≤ 100，a[i] 的绝对值至多 10000。
// 算法标签：动态规划

#include<bits/stdc++.h>
using namespace std;

int dp[10005][105];
int n,k;
int arr[10005];

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=1;i<=n;i++){
            cin>>arr[i];
        }
        dp[1][(arr[1]%k+k)%k]=dp[1][(-arr[1]%k+k)%k]=1;
        for(int i=2;i<=n;i++){
            for(int j=0;j<k;j++){
                dp[i][j]=dp[i-1][((j+arr[i])%k+k)%k]||dp[i-1][((j-arr[i])%k+k)%k];
            }
        }
        if(dp[n][0]){
            cout<<"Divisible"<<endl;
        }
        else{
            cout<<"Not divisible"<<endl;
        }
        for(int i=1;i<=n;i++){
            for(int j=0;j<k;j++){
                dp[i][j]=0;
            }
        }
    }
    return 0;
}
