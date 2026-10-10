// https://atcoder.jp/contests/fps-24/tasks/fps_24_e
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 305;
const int MOD = 998244353;

int n,m;
int fac[MAXN];
int inv[MAXN];

int c[MAXN];
int d[MAXN];

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
    cin>>n>>m;
    fac[0]=1;
    for(int i=1;i<=300;i++){
        fac[i]=(fac[i-1]*i)%MOD;
    }
    inv[300]=power(fac[300],MOD-2);
    for(int i=299;i>=0;i--){
        inv[i]=(inv[i+1]*(i+1))%MOD;
    }

    c[0]=1;
    for(int i=1;i<=m;i++){
        for(int j=0;j<=n;j++){
            for(int k=0;k<=min(i,j);k++){
                d[j]=(d[j] + (c[j-k]*inv[k]) )%MOD;
            }
        }
        for(int j=0;j<=n;j++){
            c[j]=d[j];
            d[j]=0;
        }
    }

    cout<<(c[n]*fac[n])%MOD<<endl;
    return 0;
}