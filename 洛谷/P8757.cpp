#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;
const int MOD = 1e9+7;
const int MAXH = 22;

int fac[MAXN];
int inv[MAXN];

int res2[MAXH];
int res3[MAXH];

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
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

void prepare(int n){
    fac[0]=1;
    inv[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=(fac[i-1]*i)%MOD;
    }
    inv[n]=power(fac[n],MOD-2);
    for(int i=n-1;i>=1;i--){
        inv[i]=(inv[i+1]*(i+1))%MOD;
    }
}

int comb(int a,int b){
    return fac[a]*inv[b]%MOD*inv[a-b]%MOD;
}

int all(int a,int b){
    return fac[a]*inv[b]%MOD;
}

signed main()
{
    prepare(1000000);

    res2[0]=1;
    int p=1;
    for(int i=1;i<MAXH;i++){
        p*=2;
        res2[i]=res2[i-1]+p;
    }

    res3[0]=1;
    res3[1]=4;
    p=6;
    for(int i=2;i<MAXH;i++){
        res3[i]=(i*p+res2[i-1]+res3[i-1])%MOD;
        p*=2;
    }

    // for(int i=1;i<MAXH;i++){
    //     cout<<i<<":  "<<res2[i]<<' '<<res3[i]<<endl;
    // }

    int T=read();
    while(T--){
        int n=read();
        if(n==1){
            cout<<1<<endl;
            continue;
        }
        int k=log2(n);
        int ans=0;
        ans=res2[k];
        if(3*(1<<(k-1))<=n){
            ans=(ans+res3[k])%MOD;
        }

        // cout<<' '<<ans<<' ';
        // cout<<n<<' '<<k<<' '<<all(n,k+1)<<endl;
        ans=ans*all(n,k+1)%MOD;
        cout<<ans<<endl;
    }
    return 0;
}
/*
10
1
2
3
4
5
6
7
8
9
10
*/