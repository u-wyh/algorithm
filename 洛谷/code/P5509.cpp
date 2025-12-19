#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1145141;

int n,k;
int fac[MOD+1];
int inv[MOD+1];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

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

void prepare(){
    fac[0]=1;
    inv[0]=1;
    for(int i=1;i<MOD;i++){
        fac[i]=(fac[i-1]*i)%MOD;
    }
    inv[MOD-1]=power(fac[MOD-1],MOD-2);
    for(int i=MOD-2;i>=1;i--){
        inv[i]=(inv[i+1]*(i+1))%MOD;
    }
}

int comb(int n,int m){
    if(m>n){
        return 0;
    }
    return (fac[n]*inv[m]%MOD*inv[n-m]%MOD+MOD)%MOD;
}

int lucas(int n,int m){
    if(m==0){
        return 1;
    }
    else{
        return lucas(n/MOD,m/MOD)*comb(n%MOD,m%MOD)%MOD;
    }
}

signed main()
{
    int T;
    cin>>T;
    prepare();
    while(T--){
        cin>>n>>k;
        if(n==1){
            cout<<1<<endl;
            continue;
        }
        if((k-1)%MOD==0){
            cout<<-1<<endl;
            continue;
        }
        // cout<<power(power(k-1,n-1),MOD-2)%MOD<<' '<<lucas(n*k-1,n-1)<<' ';
        int ans=power(power(k-1,n-1),MOD-2)%MOD*lucas(n*k-1,n-1)%MOD;
        ans=(ans+MOD)%MOD;
        cout<<ans<<endl;
    }
    return 0;
}