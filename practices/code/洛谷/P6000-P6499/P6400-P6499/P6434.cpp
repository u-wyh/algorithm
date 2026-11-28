// https://www.luogu.com.cn/problem/P6434
// 题意：
// 给定 n, k, l, r 以及 n 个甜品的美味值 a_i。
// 选出 k 种甜品，要求它们能按某种顺序排列，
// 使得第 i 个满足 l * prev <= curr <= r * prev。
// 方案只计 k 种甜品的组合集合（不计排列顺序）。
// 输出两行：合法方案总数 mod (10^9 + 7)，
// 以及最大美味值之和 mod (10^9 + 7)（无解均输出 0）。
// 数据范围：
// k <= 10
// k <= n <= 2 * 10^6
// 1 <= l <= r <= 10
// 1 <= a_i <= 10^9（90% 数据 a_i 随机生成）
// 难度评分：1800（洛谷分级换算）
// 算法标签：动态规划、双指针、前缀和
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e6+5;
const int MAXK = 11;
const int MOD = 1e9+7;

int n,m,l,r;
int dp[MAXN][MAXK];
int f[MAXN][MAXK];
int arr[MAXN];
int lt[MAXN],rt[MAXN];

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m>>l>>r;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    sort(arr+1,arr+n+1);
    int li=0,la=0;
    for(int i=1;i<=n;i++) {
        while(arr[la+1] * l <= arr[i] && la < i-1)
            la++;
        while(arr[li+1] * r < arr[i] && li < i-1)
            li++;
        lt[i]=li;
        rt[i]=la;
        //cout<<i<<": "<<lt[i]<<' '<<rt[i]<<endl;
    }
    //cout<<endl;
    dp[1][1]=1;
    f[1][1]=arr[1];
    for(int i=2;i<=n;i++){
        dp[i][1]=i;
        f[i][1]=arr[i];
        for(int j=2;j<=min(i,m);j++){
            dp[i][j]=dp[rt[i]][j-1]-dp[lt[i]][j-1];
            dp[i][j]+=dp[i-1][j];
            dp[i][j]%=MOD;
            if(dp[i][j]!=dp[i-1][j]){
                //后面这个式子可以加上的条件是  确实有从rt[i]转移过来的方案
                f[i][j]=max(f[i-1][j],f[rt[i]][j-1]+arr[i]);
            }
            else{
                f[i][j]=f[i-1][j];
            }
            f[i][j]%=MOD;
        }
    }
    cout<<(dp[n][m]+MOD)%MOD<<endl;
    cout<<(f[n][m]+MOD)%MOD<<endl;
    return 0;
}
