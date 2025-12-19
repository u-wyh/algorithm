#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;
const int MOD = 998244353;

int fac[MAXN];
int f[MAXN];
int g[MAXN];
int h[MAXN];

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

signed main()
{
    fac[0]=1;
    for(int i=1;i<MAXN;i++){
        fac[i]=(fac[i-1]*i)%MOD;
    }
    f[1]=1,g[1]=1,h[1]=0;
    f[2]=9,g[2]=7,h[2]=6;
    for(int i=3;i<MAXN;i++){
        h[i]=(h[i-1]*(i-2)%MOD+6*fac[i-3]%MOD)%MOD;
        g[i]=(g[i-1]*(i-1)%MOD+h[i])%MOD;
        f[i]=((f[i-1]*i)%MOD+g[i])%MOD;
    }
    int T=read();
    while(T--){
        int n=read();
        cout<<f[n]<<endl;
    }
    return 0;
}