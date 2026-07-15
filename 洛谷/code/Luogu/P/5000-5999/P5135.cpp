#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 1e6+5;

int fac[MAXN];
int inv[MAXN];

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

int comb(int n,int m){
    int ans=1;
    for(int i=1;i<=m;i++){
        ans=((n-i+1)%MOD*ans)%MOD;
    }
    ans=(ans*inv[m]%MOD+MOD)%MOD;
    return ans;
}

void prepare(){
    fac[0]=inv[0]=1;
    for(int i=1;i<=1000000;i++){
        fac[i]=(fac[i-1]*i)%MOD;
    }
    inv[1000000]=power(fac[1000000],MOD-2);
    for(int i=999999;i>=1;i--){
        inv[i]=(inv[i+1]*(i+1))%MOD;
    }
}

signed main()
{
    int T;
    T=read();
    prepare();
    while(T--){
        int n,m,op;
        n=read(),m=read(),op=read();
        if(op==1){
            if(n<m){
                cout<<0<<endl;
                continue;
            }
            cout<<comb(n,min(n-m,m))<<endl;
        }
        else{
            cout<<comb(n+m-1,min(m,n-1))<<endl;
        }
    }
    return 0;
}