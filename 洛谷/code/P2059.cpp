// https://www.luogu.com.cn/problem/P2059
// 题意：N 人围成一圈，从 1 号开始。
// 每轮从 M 张牌中等概率抽一张，按牌面数从当前庄家开始顺时针报数，报到的人出局，其下一人成为新庄家。
// 牌放回后再抽。
// 按编号输出每人最终获胜的概率，百分数保留两位小数。
// 数据范围：1 ≤ N,M ≤ 50，牌面数字在 [1,50]。

#include<bits/stdc++.h>
using namespace std;

int n,m;
int arr[55];

double f[55][55];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>arr[i];
    }
    f[1][1]=1.0;
    for(int i=2;i<=n;i++){
        for(int j=1;j<=m;j++){
            int p=(arr[j]%i==0)?i:arr[j]%i;
            for(int k=1;k<=i-1;k++){
                p++;
                if(p>i){
                    p=1;
                }
                f[i][p]+=f[i-1][k]/(1.0*m);
            }
        }
    }
    for(int i=1;i<=n;i++){
        printf("%.2lf%% ",f[n][i]*100.0);
    }
    return 0;
}
