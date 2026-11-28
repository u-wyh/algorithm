// https://www.luogu.com.cn/problem/P1655
// 题意：有 N 个可区分的球，分到 M 个不区分顺序的盒子里，
// 每个盒子都至少有一球。每球只放一个盒子，统计不同分组方案数。
// 数据范围：1 ≤ N,M ≤ 100，每个测试文件至多 10 组。
// 难度评分：1500（洛谷分级换算）
// 算法标签：动态规划、第二类斯特林数

#include<bits/stdc++.h>
using namespace std;

int n,m;
int dp[105][105];

int main()
{
    for(int i=1;i<=100;i++){
        dp[i][1]=1;
    }
    for(int i=2;i<=100;i++){
        for(int j=1;j<=i;j++){
            dp[i][j]=(dp[i-1][j-1]+dp[i-1][j]*j);
        }
    }
    while(cin>>n>>m){
        cout<<dp[n][m]<<endl;
    }
    return 0;
}
