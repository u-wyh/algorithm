// https://www.luogu.com.cn/problem/P3888
// 题意：在一个 n * m 的网格中，每个格子 (i, j) 建造油库的代价为 F_{i,j}。
// 选择若干格子建造油库，使得每个格子要么自己建有油库，要么与至少一个建有油库的格子四连通相邻。
// 求总代价最小且油库个数最少的方案（优先总代价最小，其次油库个数最少），输出油库个数和总代价。
// 数据范围：n * m <= 50 且 m <= n，0 <= F_{i,j} <= 10^5。
#include<bits/stdc++.h>
// 算法标签：状态压缩DP
using namespace std;

int n,m;
int f[55][1 << 8][1 << 8], dp[55][1 << 8][1 << 8];
int sum[55][1 << 8], nums[55][8], ans1 = INT_MAX, ans2 = INT_MAX;
int cnt[1<<8];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>nums[i][j];
        }
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<(1<<m);j++){
            for(int k=0;k<(1<<m);k++){
                f[i][j][k]=1e9;
            }
        }
    }
    for(int j=0;j<(1<<m);j++){
        for(int k=0;k<m;k++){
            if(j&(1<<k)){
                cnt[j]++;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<(1<<m);j++){
            for(int k=0;k<m;k++){
                if(j&(1<<k)){
                    sum[i][j]+=nums[i][k+1];
                }
            }
        }
    }
    for(int i=0;i<(1<<m);i++){
        f[1][i][0]=sum[1][i];
        dp[1][i][0]+=cnt[i];
    }
    for(int i=2;i<=n;i++){
        for(int j=0;j<(1<<m);j++){//当前行
            for(int k=0;k<(1<<m);k++){//上一行
                for(int u=0;u<(1<<m);u++){//上上一行
                    if(((j|k|u|k>>1|k<<1)&(1<<m)-1)==(1<<m)-1){
                        int t = f[i - 1][k][u] + sum[i][j], p = dp[i - 1][k][u] + cnt[j];
						if (f[i][j][k] > t || f[i][j][k] == t && dp[i][j][k] > p)
							f[i][j][k] = t, dp[i][j][k] = p;
                    }
                }
            }
        }
    }
    for (int i = 0; i < 1 << m; i ++)
		for (int j = 0; j < 1 << m; j ++)
			if (((i | j | i << 1 | i >> 1) & (1 << m) - 1) == (1 << m) - 1)
				if (ans1 > f[n][i][j] || f[n][i][j] == ans1 && dp[n][i][j] < ans2)
					ans1 = f[n][i][j], ans2 = dp[n][i][j];
	cout << ans2 << ' ' << ans1 <<'\n';
    return 0;
}
