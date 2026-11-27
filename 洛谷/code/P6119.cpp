// https://www.luogu.com.cn/problem/P6119
// 题意：道路左右两侧各有 N 个牧场，分别排列着 1..N 品种奶牛 a_i 和 b_j
// 满足 |a_i - b_j| <= 4 的左右牧场可连一条不相交人行道（每个牧场至多连一条），求最多可连多少条人行道。
// 数据范围：1 <= N <= 1000。
// 算法标签：动态规划
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

int n;
int a[MAXN];
int b[MAXN];
int f[MAXN][MAXN];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            f[i][j]=max(f[i-1][j],f[i][j-1]);
            if(abs(a[i]-b[j])<=4){
                f[i][j]=max(f[i][j],f[i-1][j-1]+1);
            }
        }
    }
    cout<<f[n][n]<<endl;
    return 0;
}