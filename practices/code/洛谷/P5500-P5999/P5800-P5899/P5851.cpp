// https://www.luogu.com.cn/problem/P5851
// 题意：有 N 个派（1..N）和 M 头奶牛，
// 第 i 头牛重 w_i、喜欢区间 [l_i, r_i] 内所有剩余的派；
// 需安排奶牛出场子序列使每头牛轮到时其喜欢区间内至少剩 1 个派，求最大体重和。
// 输入 N, M 及每头牛的 w_i, l_i, r_i；输出最大可能体重和。
// 数据范围：1 <= N <= 300，1 <= M <= N(N-1)/2，
// 1 <= l_i, r_i <= N，1 <= w_i <= 10^6。
// 难度评分：1800（洛谷分级换算）
// 算法标签：区间动态规划
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 305;

int n,m;
int dp[MAXN][MAXN];
int f[MAXN][MAXN][MAXN];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int w,l,r;
        cin>>w>>l>>r;
        for(int j=l;j<=r;j++){
            f[l][r][j]=w;
        }
    }
    for(int len=1;len<=n;len++){
		for(int i=1;i+len-1<=n;i++){
			int j = i+len-1;
			for(int k=i;k<=j;k++){
				f[i][j][k] = max(f[i][j][k],max(f[i+1][j][k],f[i][j-1][k]));
			}
		}
	}
	for(int len=1;len<=n;len++){
        for(int i=1;i+len-1<=n;i++){
            int j=i+len-1;
            for(int k=i;k<=j;k++){
                dp[i][j]=max(dp[i][j],dp[i][k]+dp[k+1][j]);
            }
            for(int k=i;k<=j;k++){
                dp[i][j]=max(dp[i][j],dp[i][k-1]+dp[k+1][j]+f[i][j][k]);
            }
        }
	}
	cout<<dp[1][n]<<endl;
    return 0;
}
