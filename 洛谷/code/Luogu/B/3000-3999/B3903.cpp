#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 1e5+5;

int n,x,tmp;
int a,b,c,d;
int fac[MAXN];
int inv[MAXN];
int val[MAXN];

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
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

void build(){
    fac[0]=inv[0]=1;
    fac[n+1]=inv[n+1]=1;
    for(int i=1;i<=n;i++){
        fac[i]=(fac[i-1]*i)%MOD;
    }
    inv[n]=power(fac[n],MOD-2);
    for(int i=n-1;i>=1;i--){
        inv[i]=(inv[i+1]*(i+1))%MOD;
    }
}

void prepare(){
    tmp=x;
    while((tmp-(tmp&(-tmp)))){
        tmp-=tmp&(-tmp);
    }
    for(int i=1;i<=n;i++){
        if(val[i]==tmp){
            a++;
        }
        else if(val[i]+tmp>x){
            b++;
        }
        else{
            c++;
        }
        if(val[i]>=x){
            d++;
        }
    }
}

int comb(int n,int m){
    // if(n==m){
    //     return 1;
    // }
    return fac[n]*inv[n-m]%MOD*inv[m]%MOD;
}

signed main()
{
    n=read(),x=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    build();
    prepare();
    if(d||(a>c+1)){
        cout<<0<<endl;
        return 0;
    }
    if(tmp==x){
        cout<<fac[n]<<endl;
        return 0;
    }
    int ans=1;
    ans=fac[a]*fac[b]%MOD*fac[c]%MOD;
    ans=(ans*comb(c+1,a)%MOD*comb(c+b-a,c-a))%MOD;
    // for(int i=1;i<=min(c+1-a,b);i++){
    //     ans=(ans*comb(c+1-a,i))%MOD;
    // }
    ans=(ans+MOD)%MOD;
    cout<<ans<<endl;
    cout<<comb(0,0)<<endl;
    return 0;
}