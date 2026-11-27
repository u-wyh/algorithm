// https://www.luogu.com.cn/problem/P2964
// 题意：输入硬币数量 n，以及从左至右排成一行的每枚硬币价值 c_i。
// 小 A 与小 B 轮流从当前序列最左侧连续取硬币累加到各自总价值，
// 小 A 首轮最多取 2 枚；
// 之后若对方上轮取了 k 枚，本轮最多可取 2k 枚，取完结束。
// 求双方均尽量最大化各自累计价值时，小 A 能获得的最大累计价值。
// 输出一行一个整数，表示小 A 能获得的最大累计价值。
// 数据范围：对于 100% 的数据，5 <= n <= 2*10^3，
// 1 <= c_i <= 10^5（空间限制 20 MiB）。
// 算法标签：动态规划、博弈论、前缀和
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2005;

int n;
int arr[MAXN];
int dp[MAXN][MAXN];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        arr[i]+=arr[i-1];
    }
    for(int i=n;i>=1;i--){
        for(int j=1;j<=n-i+1;j++){
            int k=arr[n]-arr[i-1]-dp[i+j][min(j*2,n-i-j+1)];
            dp[i][j]=max(dp[i][j-1],k);
        }
    }
    cout<<dp[1][2]<<endl;
    return 0;
}
