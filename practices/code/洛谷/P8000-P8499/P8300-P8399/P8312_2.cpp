// https://www.luogu.com.cn/problem/P8312
// 题意：给定 n 点 m 边的有向图，
// 第 i 条边从 a_i 到 b_i 耗时 t_i 分钟。
// q 次询问从 c_j 到 d_j 最多乘坐 k 条边（公交线路）的最短时间；
// 由样例可知若无法到达则输出 -1（起点终点相同为 0）。
// 数据范围：100% 数据满足 2 <= n <= 70，
// 1 <= m, t_i <= 10^6，
// 1 <= a_i, b_i, c_j, d_j <= n
// 1 <= k <= 10^9，1 <= q <= n^2。
// 难度评分：1400（洛谷分级换算）
// 算法标签：动态规划、最短路
#include<bits/stdc++.h>
using namespace std;

long long n,m,k,q,s,t,f[100][100],a[100][100],b[100][100];

int main(){
    scanf("%lld%lld",&n,&m);
    //初始化
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			f[i][j]=INT_MAX;
   		}
    }
	for(int i=1;i<=m;i++){
		long long x,y,z;
		scanf("%lld%lld%lld",&x,&y,&z);
		f[x][y]=min(f[x][y],z);//多条重边取最短的一条
	}
	scanf("%lld%lld",&k,&q);
    //初始化a
	for (int i=1;i<=n;i++){
		for (int j=1;j<= n;j++){
			a[i][j]=f[i][j];
		}
	}
	k=min(k,n);
	for(int kk=2;kk<=k;kk++){//跑k次
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				b[i][j]=a[i][j];
			}
		}
		for(int lg=1;lg<=n;lg++){
			for (int i=1;i<=n;i++){
				for (int j=1;j<=n;j++){
					b[i][j]=min(b[i][j],a[i][lg]+f[lg][j]);//只转移一条边
				}
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
			    a[i][j]=b[i][j];//更新
			}
		}
	}
	for(int i=1;i<=q;i++){
		scanf("%lld%lld",&s,&t);
		if(s==t)printf("0\n");//特判s=t的情况
		else if(a[s][t]==INT_MAX)printf("-1\n");//无法到达
		else printf("%d\n",a[s][t]);
	}
	return 0;
}
