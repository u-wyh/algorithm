#include<bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
const int MAXN = 1e6+5;
const int MAXM = 1e4+5;

long long n;
long long fac[MAXM];
int dp[MAXM][MAXM];
int len;
int pos1[MAXN],pos2[MAXN];

signed main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        len=0;
        for(int i=1;1ll*i*i<=n;i++){
            if(n%i){
                continue;
            }
            fac[++len]=i;
            if(1ll*i*i!=n){
                fac[++len]=n/i;
            }
        }
        // cout<<' '<<len<<endl;
        sort(fac+1,fac+len+1);
        for(int i=1;i<=len;i++){
            for(int j=1;j<=len;j++){
                dp[i][j]=0;
            }
        }
        int q=sqrt(n);
        for(int i=1;i<=len;i++){
            dp[i][i]=1;
            if(fac[i]<=q){
                pos1[fac[i]]=i;
            }
            else{
                pos2[n/fac[i]]=i;
            }
        }
        // cout<<888<<endl;
        for(int i=1;i<=len;i++){
            for(int j=1;j<=len;j++){
                dp[i][j]+=dp[i][j-1];
                if(i<=j){
                    continue;
                }
                if(fac[i]%fac[j]==0){
                    long long tmp=fac[i]/fac[j];
                    if(tmp<=q){
                        dp[i][j]+=dp[pos1[tmp]][j-1];
                    }
                    else{
                        dp[i][j]+=dp[pos2[n/tmp]][j-1];
                    }
                }
                dp[i][j]%=MOD;
            }
        }
        cout<<(dp[len][len]-1+MOD)%MOD<<endl;
    }
    return 0;
}