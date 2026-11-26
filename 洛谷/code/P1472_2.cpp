// https://www.luogu.com.cn/problem/P1474
// 题意：输入两个整数 n 和 k。
// 求恰好有 n 个节点、深度为 k 的无标号完满二叉树有多少种。
// 完满指每个节点儿子数为 0 或 2，根节点深度为 1。
// 输出方案数对 9901 取模的结果。
// 数据范围：
// 3 <= n < 200（节点数）
// 2 <= k < 100（树的深度）
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