// https://www.luogu.com.cn/problem/P3120
// 题意：输入网格行数 R、列数 C、颜色数 K，以及 R*C 的网格颜色标号。
// 从左上角 (1, 1) 出发跳到右下角 (R, C)，
// 每次跳跃必须满足目标格行号严格更大、列号严格更大，且两格标号不同。
// 求从左上角到右下角的合法跳跃方案总数，对 10^9+7 取模。
// 输出一个整数表示方案数模 10^9+7 的结果。
// 数据范围：2 <= R, C <= 750，1 <= K <= R*C。
// 难度评分：1800（洛谷分级换算）
// 算法标签：动态规划、前缀和优化
#include <bits/stdc++.h>
#define MOD 1000000007
static char buf[1000000],*paa=buf,*pd=buf;
#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
inline int read(void) {
	register int x(0);register char c(getchar());
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x;
}
int R,C,K,dp[759][759],a[759][759];
long long v[759*759];
signed main(void) {
	R=read();C=read();K=read();
	for(int i=1;i<=R;i++) {
		for(int j=1;j<=C;j++) {
			a[i][j]=read();
		}
	}
	dp[1][1]=1;
	for(int i=2;i<=R;i++) {
		memset(v,0,sizeof(v));
		long long as=0;
		for(int j=2;j<=C;j++) {
			for(int k=1;k<i;k++) {
				v[a[k][j-1]]+=dp[k][j-1];
				as+=dp[k][j-1];
			}
			dp[i][j]=((as-v[a[i][j]])%MOD+MOD)%MOD;
		}
	}
	printf("%d",dp[R][C]);
	return 0;
}
