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
