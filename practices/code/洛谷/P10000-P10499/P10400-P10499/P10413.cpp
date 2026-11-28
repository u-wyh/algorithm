// https://www.luogu.com.cn/problem/P10413
// 题意：圆周上有 2023 个有编号的点，任选点对连线。
// 每个点最多参与一条线，所有线段彼此不相交。
// 输出：不同连线方案数对 2023 取模的结果。
// 数据范围：点数和模数均固定为 2023。
// 难度评分：1300（洛谷分级换算）
// 算法标签：组合计数、卡特兰数、动态规划

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
