// https://www.luogu.com.cn/problem/P1474
// 题意：给 V 种面值的货币和目标面值 N。
// 每种货币数量无限，求凑出总面值 N 的
// 不同方案数（不计货币顺序）。
// 输出：一行一个整数，表示总方案数。
// 数据范围：1 <= V <= 25，1 <= N <= 10000，
// 答案在 64 位带符号整数范围内。
// 算法标签：完全背包、动态规划
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e4+5;

int n,m;
int a[26];
int c[MAXN];
int d[MAXN];

void compute(){
    c[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            for(int k=0;k<=j;k+=a[i]){
                d[j]+=c[j-k];
            }
        }
        for(int j=0;j<=m;j++){
            c[j]=d[j];
            d[j]=0;
        }
    }

    cout<<c[m]<<endl;
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }

    compute();

    return 0;
}