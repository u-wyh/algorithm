// https://www.luogu.com.cn/problem/P1472
// 题意：求有 n 个节点、深度恰好为 k 的无标号二叉树形状数，每个节点必须有 0 或 2 个孩子，左、右孩子的位置要区分。根的深度为 1，结果对 9901 取模。
// 数据范围：3 ≤ n < 200，2 ≤ k < 100。

#include<bits/stdc++.h>
using namespace std;
const int MOD = 9901;

int n,m;
int f[205][105];

int main()
{
    cin>>n>>m;
    for(int k=1;k<=m;k++){
        f[1][k]=1;
    }
    for(int k=2;k<=m;k++){
        for(int i=3;i<=n;i+=2){
            for(int j=1;j<i;j+=2){
                f[i][k]+=(f[j][k-1]*f[i-j-1][k-1]);
                f[i][k]%=MOD;
            }
        }
    }
    cout<<((f[n][m]-f[n][m-1])%MOD+MOD)%MOD<<endl;
    return 0;
}
