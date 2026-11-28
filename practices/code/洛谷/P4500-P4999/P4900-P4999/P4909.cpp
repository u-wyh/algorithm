// https://www.luogu.com.cn/problem/P4909
// 题意：由 N 个端点 (i, H_i) 构成的折线山脉，
// 要在起点 1、终点 N 及若干中间端点建支柱拉缆绳
// 要求每段缆绳水平跨度不超过 K 且线段不低于中间任何山脉端点的高度，
// 求最少支柱总数。
// 数据范围：2 <= N <= 5000，1 <= K <= N-1，
// 0 <= H_i <= 10^9。
// 难度评分：1900（洛谷分级换算）
// 算法标签：动态规划、计算几何
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5005;

int n,m;
int arr[MAXN];
int f[MAXN];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        f[i]=1e9;
    }
    f[1]=1;
    for(int i=1;i<=n;i++){
        double x=INT_MIN;
        for(int j=1;j<=m&&i+j<=n;j++){
            if(x<=1.0*(arr[i+j]-arr[i])/j){
                f[i+j]=min(f[i+j],f[i]+1);
                x=1.0*(arr[i+j]-arr[i])/j;
            }
        }
    }
    cout<<f[n]<<endl;
    return 0;
}
