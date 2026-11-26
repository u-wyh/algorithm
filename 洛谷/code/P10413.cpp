// https://www.luogu.com.cn/problem/P10413
// 题意：圆周上有 2023 个编号点，可以挑一些点对连线。问有多少种连线方案，使线段在圆内互不交叉。只提交方案数对 2023 取模的结果。
// 数据范围：点数固定为 2023，模数为 2023。

#include<bits/stdc++.h>
using namespace std;
const int n=2023,mod=2023;

long long c[n+9][n+9],h[n+9]={1,1},ans=1;

signed main(){
	for(int i=0;i<=n;i++)c[i][0]=1;
	for(int i=0;i<=n;i++)for(int j=1;j<=i;j++)c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
    for(int i=2;i<=n;i++)for(int j=0;j<=i-1;j++)h[i]=(h[i]+h[j]*h[i-j-1]%mod)%mod;
	for(int i=1;i<=n;i++)if(i%2==0)ans=(ans+c[n][i]*h[i/2]%mod)%mod;
	cout<<ans;
}
