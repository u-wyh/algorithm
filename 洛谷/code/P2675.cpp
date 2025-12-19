#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 10007;

int n;
int fun[200][200];
int fac[MOD],inv[MOD];

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        a=(a*a)%MOD;
        b>>=1;
    }
    return ans;
}

void build(){
    fac[0]=inv[0]=1;
    for(int i=1;i<MOD;i++){
        fac[i]=(fac[i-1]*i)%MOD;
    }
    inv[MOD-1]=power(fac[MOD-1],MOD-2);
    for(int i=MOD-2;i>=1;i--){
        inv[i]=(inv[i+1]*(i+1))%MOD;
    }
}

int comb(int a,int b){
    // cout<<999<<' '<<a<<' '<<b<<endl;
    if(b>a){
        return 0;
    }
    return ((fac[a]*inv[b]%MOD)*inv[a-b]%MOD+MOD)%MOD;
}

int lucas(int n,int m){
    if(m==0){
        return 1;
    }
    if(n<200&&m<200){
        if(fun[n][m]!=-1){
            return fun[n][m];
        }
    }
    int k=((lucas(n/MOD,m/MOD)*comb(n%MOD,m%MOD))%MOD+MOD)%MOD;
    if(n<200&&m<200){
        fun[n][m]=k;
    }
    return k;
}

signed main()
{
    cin>>n;
    if(n==0){
        cout<<0<<endl;
        return 0;
    }
    if(n==1){
        cout<<1<<endl;
        return 0;
    }
    build();
    for(int i=0;i<200;i++){
        for(int j=0;j<200;j++){
            fun[i][j]=-1;
        }
    }
    int ans=0;
    if(n%2==1){
        ans+=(n%MOD*lucas(n-1,(n-1)/2));
    }
    else{
        ans+=((2*n-1)%MOD*lucas(n-1,(n-1)/2));
    }
    int k=3;
    for(int i=0;i<=(n-1)/2-1;i++){
        ans+=lucas(n-1,i)*k%MOD;
        k+=4;
        k%=MOD;
    }
    ans=(ans%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}