// https://www.luogu.com.cn/problem/P5505
// 题意：有 m 种特产（数量已知），分给 n 个同学，要求每个同学至少分到 1 个特产，求总分配方案数对 10^9+7 取模的结果。
// 输入 n, m 及每种特产的数量；输出总方案数模 10^9+7。
// 数据范围：1 <= n, m <= 1000，每种特产数量不超过 1000。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXK = MAXN*2;
const int MOD = 1e9+7;

int nums[MAXN];
long long c[MAXK][MAXK];
long long g[MAXN];
int n,m,k;

long long compute(){
    for(int i=0;i<k;i++){
        c[i][0]=c[i][i]=1;
        for(int j=1;j<i;j++){
            c[i][j]=(c[i-1][j]+c[i-1][j-1])%MOD;
        }
    }
    for(int i=0;i<n;i++){
        g[i]=c[n][i];
        for(int j=1;j<=m;j++){
            g[i]=(g[i]*c[nums[j]+n-i-1][n-i-1]%MOD);
        }
    }
    g[n]=0;
    long long ans=0;
    for(int i=0;i<=n;i++){
        if(i&1){
            ans=(ans+g[i]*(MOD-1)%MOD)%MOD;
        }
        else{
            ans=(ans+g[i])%MOD;
        }
    }
    return ans;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>nums[i];
    }
    k=2*n;
    cout<<compute();
    return 0;
}