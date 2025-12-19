#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 5e5+5;

int n,k;
int nums[MAXN];
int f[MAXN];
int g[MAXN];

signed main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=1;i<=n;i++){
            cin>>nums[i];
        }
        f[0]=0,g[0]=1;
        f[1]=0,g[1]=1;
        for(int i=2;i<=n;i++){
            f[i]=0,g[i]=0;
            if(nums[i]==nums[i-1]){
                f[i]=0;
                g[i]=(g[i-1]+f[i-1])%MOD;
            }
            else{
                g[i]=(g[i-1]+f[i-1])%MOD;
                int j=i-1;
                while(j>=1&&nums[j]!=nums[i]){
                    f[i]=(f[i]+f[j-1]+g[j-1])%MOD;
                    j--;
                }
            }
            // cout<<f[i]<<' '<<g[i]<<endl;
        }
        int ans=(f[n]+g[n])%MOD;
        cout<<ans<<endl;
    }
    return 0;
}