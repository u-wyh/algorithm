#include<bits/stdc++.h>
using namespace std;

int d[1010],dp[1010][1010];
int p[1010][1010],q[1010][1010];

int main()
{
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
            scanf("%d",&d[i]);
		for(int i=1;i<=n;i++)
            d[i]=d[i-1]+d[i];//前缀和
		for(int len=1;len<=n;len++){
			for(int i=1;i<=n-len+1;i++){
			    int j=i+len-1;
				dp[i][j]=d[j]-d[i-1]-min(0,min(p[i][j-1],q[i+1][j]));//状态转移
				p[i][j]=min(p[i][j-1],dp[i][j]);
                q[i][j]=min(q[i+1][j],dp[i][j]);//更新
			}
		}
		printf("%d\n",dp[1][n]);//输出答案
	}
	return 0;
}
