#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 1e6+5e3+5;
const int MOD = 1e9+7;
const int MAXM = 5e3+5;

int n,m;
int nums[MAXM];
int cnt[MAXN];
int p[MAXM];
int comb[MAXM][MAXM];

signed main()
{
    cin>>n>>m;
    int val=0;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        val=max(val,nums[i]);
    }
    for(int i=0;i<=m;i++){
        comb[i][0]=1;
        for(int j=1;j<=i;j++){
            comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%MOD;
        }
    }
    p[0]=1;
    for(int i=1;i<=m;i++){
        p[i]=(p[i-1]*(n-1))%MOD;
    }
    cnt[0]=0;
    for(int i=1;i<=val+m;i++){
        cnt[i]=cnt[i-(i&-i)]+1;
        // cout<<i<<" : "<<cnt[i]<<endl;
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            ans=(ans+(((p[m-j]*cnt[nums[i]+j])%MOD)*comb[m][j])%MOD)%MOD;
        }
    }
    ans=(ans+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}