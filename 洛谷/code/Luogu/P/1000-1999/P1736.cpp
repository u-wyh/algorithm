#include <bits/stdc++.h>
using namespace std;

int n,m;
int a[2501][2501],dp[2501][2501][2];
int ans=0;

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]){
				int l=dp[i-1][j-1][0]+1,r=dp[i-1][j+1][1]+1,k;
				for(k=1;k<=dp[i-1][j-1][0];k++)
					if(a[i-k][j]||a[i][j-k]){
						l=k;
						break;
					}
				for(k=1;k<=dp[i-1][j+1][1];k++)
					if(a[i-k][j]||a[i][j+k]){
						r=k;
						break;
					}
				dp[i][j][0]=l,dp[i][j][1]=r,ans=max(max(dp[i][j][0],dp[i][j][1]),ans);
			}
	cout<<ans;
}
