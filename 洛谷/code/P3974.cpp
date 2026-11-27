// https://www.luogu.com.cn/problem/P3974
// 题意：第一行输入数据组数 t；每组数据输入网格行数 n、列数 m，以及 n * m 矩阵表示每格的财宝数（0 表示无财宝）。
// 每次从左上角出发，只能向右或向下走，每次经过一个格子至多捡走一块财宝。
// 对每组数据输出把所有财宝全部捡完所需的最少出行次数。
// 数据范围：对于 100% 的数据，1 <= t <= 2，1 <= n, m <= 1000，每个格子的财宝数不超过 10^6。
#include<bits/stdc++.h>
// 算法标签：动态规划
using namespace std;
const int MAXN = 1e3+5;

int n,m;
int val[MAXN][MAXN];
long long dp[MAXN][MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int main()
{
    int T=read();
    while(T--){
        n=read(),m=read();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                val[i][j]=read();
            }
        }
        for(int i=0;i<=n;i++){
            for(int j=1;j<=m+1;j++){
                dp[i][j]=0;
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=m;j>=1;j--){
                dp[i][j]=max(max(dp[i-1][j],dp[i][j+1]),dp[i-1][j+1]+val[i][j]);
            }
        }
        cout<<dp[n][1]<<endl;
    }
    return 0;
}