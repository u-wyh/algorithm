#include<bits/stdc++.h>
using namespace std;

int n,m,k;
int dp[1005][105];
int a[105],x[105];

bool cmp(int a,int b){
    return a>b;
}

int main()
{
    cin>>n>>m>>k;
    int sum=0;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>x[i];
        sum+=x[i];
    }
    if (sum<=m)	{
		int ans=0;
		sort(a+1,a+1+n,cmp);
		for (int i=1;i<=k;i++)
			ans+=a[i]*2;
		for (int i=k+1;i<n;i++)
			ans+=a[i];
		cout<<ans;
		return 0;
	}
	int ans=0;
	for(int i=1;i<=n;i++){
        for(int j=m;j>=x[i];j--){
            for(int l=min(k,i);l>=1;l--){
                dp[j][l]=max(dp[j][l],max(dp[j-x[i]][l]+a[i],dp[j-x[i]][l-1]+2*a[i]));
                ans=max(ans,dp[j][l]);
            }
            dp[j][0]=max(dp[j][0],dp[i-x[i]][0]+a[i]);
            ans=max(ans,dp[j][0]);
        }
	}
	cout<<ans<<endl;
    return 0;
}
