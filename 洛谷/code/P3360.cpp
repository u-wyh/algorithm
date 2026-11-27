// https://www.luogu.com.cn/problem/P3360
// 题意：第 1 行输入警察到达进口的时间 n，第 2 行按深度优先顺序给出若干组 (t, x)：经过走廊耗 t 秒（进出需各走一次即 2t）
// x=0 表示分支成两条走廊，x>0 表示该展览厅有 x 幅画，随后给出每幅画的 (价值 w, 偷取时间 c)。
// 在警察到达之前（总耗时严格小于 n 秒）从进口出发偷画并返回进口逃脱。
// 输出能获得的最大总价值。
// 数据范围：n <= 600，t <= 5，x <= 30，w <= 10^6，c <= 5，房间和走廊总数不超过 300。
#include<bits/stdc++.h>
// 算法标签：树形动态规划、0-1背包
using namespace std;

int s,dp[10010][10010],ans,a[2010],b[2010];

void read(int x){

	int t,k;
	cin>>t>>k;
	t=t<<1;
	if(k>0){
		for(int i=1;i<=k;i++){
			cin>>a[i]>>b[i];
		}
		for(int i=1;i<=k;i++){
			for(int j=s;j>=t+b[i];j--){
				dp[x][j]=max(dp[x][j-b[i]]+a[i],dp[x][j]);
			}
		}
	}
	if(!k){
		read(x<<1);
		read(x<<1|1);
		for(int i=s;i>=t;i--)
			for(int j=0;j<=i-t;j++){
				dp[x][i]=max(dp[x][i],dp[x<<1][j]+dp[x<<1|1][i-j-t]);
			}
	}
}
int main()
{
	cin>>s;
	s--;
	read(1);
	cout<<dp[1][s];
	return 0;
}
