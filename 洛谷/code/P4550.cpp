// https://www.luogu.com.cn/problem/P4550
// 题意：共有 n 种邮票，每次等概率随机买到其中一种，第 k 次购买花费 k 元，求集齐全部 n 种邮票所需总花费的期望（保留两位小数）。
// 数据范围：n <= 10000。
#include<bits/stdc++.h>
// 算法标签：概率期望、递推
using namespace std;
const int MAXN = 1e4+5;

double f[MAXN];
double g[MAXN];

int main()
{
    int n;
    cin>>n;
    for(int i=n-1;i>=0;i--){
        f[i]=f[i+1]+1.0*n/(n-i);
        g[i]=1.0*i/(n-i)*f[i]+g[i+1]+f[i+1]+1.0*n/(n-i);
    }
    printf("%.2lf",g[0]);
    return 0;
}