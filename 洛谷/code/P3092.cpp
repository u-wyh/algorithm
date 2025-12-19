#include<bits/stdc++.h>
using namespace std;

int n,m;
int coin[17],shop[100005];
int sum[100005];
int dp[1<<17],f[1<<17];
int ans=INT_MAX;

int check(int left, int limit) {
	int l = left, r = m, mid;
	int ans=left;
	while(l<=r){
        mid=(l+r)/2;
        if(sum[mid]-sum[left]<=limit){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
	}
	return ans;
}

int main()
{
    cin>>n>>m;
    int tot=0;
    for(int i=1;i<=n;i++){
        cin>>coin[i];
        tot+=coin[i];
    }
    //cout<<' '<<tot<<endl;;
    for(int i=1;i<=m;i++){
        cin>>shop[i];
        sum[i]=sum[i-1]+shop[i];
    }
//    for(int i=1;i<=m;i++){
//        cout<<sum[i]<<' ';
//    }
//    cout<<endl;
//    sum[0]=shop[0];
//    for(int i=1;i<m;i++){
//        sum[i]=sum[i-1]+shop[i];
//    }
    for(int i=2;i<(1<<(n+1));i++){
        for(int j=1;j<=n;j++){
            if(i&(1<<j)){
                int sum=check(dp[i^(1<<j)],coin[j]);
                if(sum>dp[i]){
                    dp[i]=sum;
                    f[i]=f[i^(1<<j)]+coin[j];
                    if(dp[i]==m){
                        ans=min(ans,f[i]);
                    }
                }
            }
        }
        //cout<<i<<' '<<dp[i]<<' '<<f[i]<<endl;
    }
    //cout<<endl;
    if(tot-ans<0)
        ans=-1;
    else
        ans=tot-ans;
    cout<<ans;
    return 0;
}
