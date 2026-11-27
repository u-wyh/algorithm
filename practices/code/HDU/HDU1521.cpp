// https://acm.hdu.edu.cn/showproblem.php?pid=1521
// 题意：多组数据，每组给 n 种物品和每种的数量。
// 从中选 m 个排成一列，同种物品视为相同。
// 输出：每组输出不同的排列方案数。
// 数据范围：1 <= n, m <= 10，
// 题面保证运算结果不超过 2^31。
// 算法标签：生成函数、动态规划
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 15;

int n,m;
int a[MAXN];
int fac[MAXN];
int c[MAXN];
int d[MAXN<<1];

void init(){
    fac[0]=1;
    for(int i=1;i<=12;i++){
        fac[i]=fac[i-1]*i;
    }
}

int compute(){
    init();
    for(int i=0;i<=a[1];i++){
        c[i]=fac[m]/fac[i];
    }
    for(int i=2;i<=n;i++){
        for(int j=0;j<=m;j++){
            for(int k=0;k<=a[i]&&j+k<=m;k++){
                d[j+k]+=c[j]/fac[k];
            }
        }
        for(int j=0;j<=m;j++){
            c[j]=d[j],d[j]=0;
        }
    }
    return c[m];
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    cout<<compute()<<endl;
    return 0;
}