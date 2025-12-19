#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1004535809;
const int MAXN = 1005;

int n;
int c[MAXN][MAXN];
int f[MAXN];
int g[MAXN];

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

signed main()
{
    cin>>n;
    for(int i=0;i<=n;i++){
        c[i][0]=c[i][i]=1;
        for(int j=1;j<i;j++){
            c[i][j]=(c[i-1][j-1]+c[i-1][j])%MOD;
        }
    }
    g[1]=1;
    for(int i=2;i<=n;i++){
        g[i]=power(2,c[i][2]);
    }
    f[1]=1;
    for(int i=2;i<=n;i++){
        f[i]=g[i];
        for(int j=1;j<i;j++){
            f[i]=(f[i]-((c[i-1][j-1]*f[j])%MOD*g[i-j])%MOD)%MOD;
        }
        f[i]=(f[i]+MOD)%MOD;
    }
    cout<<f[n]<<endl;
    return 0;
}