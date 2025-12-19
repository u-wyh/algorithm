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
