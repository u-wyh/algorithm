#include<bits/stdc++.h>
#define int long long
using namespace std;
int c;
int v[15],dp[100005][15],a[100005];
int p10[15]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
void mian(){
	string n;cin>>n;int l=n.length();
	for(int i=0;i<l;i++)a[i+1]=n[i]-'0';
	for(int i=1;i<=9;i++)cin>>v[i];
	memset(dp,0,sizeof dp);
	int s=0;
	for(int i=1;i<=l;i++)s+=v[a[i]];
	for(int i=l;i>=1;i--){
		for(int j=1;j<=min(9ll,l-i+1);j++){
			dp[i][j]=max(dp[i+1][j],dp[i+1][j-1]+v[a[i]]-p10[j-1]*a[i]);
		}
	}
	int ans=0;
	for(int i=1;i<=9;i++)ans=max(ans,dp[1][i]);
	cout<<s-ans<<endl;
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>c;
	int t;cin>>t;
	while(t--)mian();
	return 0;
}
