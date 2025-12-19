#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXK = MAXN*2;
const int MOD = 1e9+7;

int nums[MAXN];
long long c[MAXK][MAXK];
long long g[MAXN];
int n,m,k;

long long compute(){
    for(int i=0;i<k;i++){
        c[i][0]=c[i][i]=1;
        for(int j=1;j<i;j++){
            c[i][j]=(c[i-1][j]+c[i-1][j-1])%MOD;
        }
    }
    for(int i=0;i<n;i++){
        g[i]=c[n][i];
        for(int j=1;j<=m;j++){
            g[i]=(g[i]*c[nums[j]+n-i-1][n-i-1]%MOD);
        }
    }
    g[n]=0;
    long long ans=0;
    for(int i=0;i<=n;i++){
        if(i&1){
            ans=(ans+g[i]*(MOD-1)%MOD)%MOD;
        }
        else{
            ans=(ans+g[i])%MOD;
        }
    }
    return ans;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>nums[i];
    }
    k=2*n;
    cout<<compute();
    return 0;
}