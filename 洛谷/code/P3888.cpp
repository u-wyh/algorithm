#include<bits/stdc++.h>
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
