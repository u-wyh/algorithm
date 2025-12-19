#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 2e6+5;

int n,m;
int a,b;
char s[MAXN];
int fac[MAXN];
int inv[MAXN];
int sum[MAXN];

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

void build(int n){
    fac[0]=1;
    inv[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=(fac[i-1]*i)%MOD;
    }
    inv[n]=power(fac[n],MOD-2);
    for(int i=n-1;i>=1;i--){
        inv[i]=(inv[i+1]*(i+1))%MOD;
    }
    sum[0]=1;
    for(int i=1;i<=b;i++){
        int val=fac[b]*inv[i]%MOD*inv[b-i]%MOD;
        sum[i]=(sum[i-1]+val)%MOD;
    }
}

int comb(int a,int b){
    if(b>a){
        return 0;
    }
    return fac[a]*inv[b]%MOD*inv[a-b]%MOD;
}

signed main()
{
    scanf("%lld %lld %s",&n,&m,s+1);
    a=0,b=0;
    for(int i=1;i<=n;i++){
        if(s[i]=='A'){
            a++;
        }
        else if(s[i]=='B'){
            b++;
        }
    }
    build(MAXN-1);
    int ans=0;
    for(int i=0;i<=a&&i<=m;i++){
        int j=min((m-i),b);
        ans=(ans+(power(2,i)*comb(a,i))%MOD*sum[j]%MOD)%MOD;
    }

    cout<<ans<<endl;
    return 0;
}