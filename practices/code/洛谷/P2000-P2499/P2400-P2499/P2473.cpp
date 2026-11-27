// https://www.luogu.com.cn/problem/P2473
// 题意：共 k 轮，每轮等概率随机出现 n 种宝物之一，可吃或不吃。
// 第 i 种宝物分值 p_i（可负），
// 需先吃过其前提集合 s_i 中的所有宝物才能吃它。
// 求最优策略下的期望总分，保留六位小数。
// 数据范围：1 <= k <= 100，1 <= n <= 15，
// -10^6 <= p_i <= 10^6。
// 算法标签：期望动态规划、状态压缩动态规划
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXM = 1<<16;

int k,n;
int sta[20];
int val[20];
double dp[MAXN][MAXM];

int main()
{
    cin>>k>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        int x;
        while(cin>>x&&x){
            sta[i]|=(1<<(x-1));
        }
    }
    int status=1<<n;
    for(int i=1;i<=k;i++){
        for(int j=0;j<status;j++){
            for(int p=1;p<=n;p++){
                if((sta[p]&j)==sta[p]){
                    dp[i][j]+=max(dp[i-1][j],dp[i-1][j|(1<<(p-1))]+val[p])/n;
                }
                else{
                    dp[i][j]+=dp[i-1][j]/n;
                }
            }
        }
    }
    printf("%.6lf",dp[k][0]);
    return 0;
}