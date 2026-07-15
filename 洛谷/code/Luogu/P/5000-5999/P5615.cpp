#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 5005;

int n;
int f1[MAXN],f2[MAXN];
int g1[MAXN],g2[MAXN];
int ans[MAXN];

long long power(long long a,long long b){
    long long ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        a=(a*a)%MOD;
        b>>=1;
    }
    return ans;
}

signed main()
{
    n=5000;
    f1[0]=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<=min(n+1,i*(i+1)/2);j++){
            f2[j]=(f2[j]+f1[j])%MOD;
            f2[min(j+i+1,n+1)]=(f2[min(j+i+1,n+1)]+f1[j])%MOD;
            g2[j]=(g2[j]+g1[j])%MOD;
            g2[min(j+i+1,n+1)]=(g2[min(j+i+1,n+1)]+g1[j]+f1[j])%MOD;
        }
        if(i>=3){
            for(int j=i+2;j<=n+1;j++){
                ans[i+1]=(ans[i+1]+f1[j]+g1[j])%MOD;
            }
            ans[i+1]=(ans[i+1]+ans[i])%MOD;
        }
        for(int j=0;j<=n+1;j++){
            f1[j]=f2[j];
            g1[j]=g2[j];
            f2[j]=0;
            g2[j]=0;
        }
    }
    // f[0][0]=1;
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<=min(n+1,i*(i+1)/2);j++){
    //         f[i+1][j]=(f[i+1][j]+f[i][j])%MOD;
    //         f[i+1][min(j+i+1,n+1)]=(f[i+1][min(j+i+1,n+1)]+f[i][j])%MOD;
    //     }
    // }
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<=min(n+1,i*(i+1)/2);j++){
    //         g[i+1][j]=(g[i+1][j]+g[i][j])%MOD;
    //         g[i+1][min(j+i+1,n+1)]=(g[i+1][min(j+i+1,n+1)]+f[i][j]+g[i][j])%MOD;
    //     }
    // }
    // for(int i=4;i<=n;i++){
    //     for(int j=i+1;j<=n+1;j++){
    //         ans[i]=(ans[i]+f[i-1][j]+g[i-1][j])%MOD;
    //     }
    //     ans[i]=(ans[i]+ans[i-1])%MOD;
    // }
    int T;
    cin>>T;
    while(T--){
        long long inv;
        long long res;
        cin>>inv;
        res=ans[inv];
        inv=power(power(2,inv),MOD-2);
        res*=inv;
        res%=MOD;
        cout<<res<<endl;
    }
    return 0;
}