#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;
const int MOD = 998244353;

int n;
int ans;
int val[MAXN];
int sz[MAXN];

int ls[MAXN];
int rs[MAXN];
int st[MAXN];

int fac[MAXN<<1];
int inv[MAXN<<1];

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
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=(fac[i-1]*i)%MOD;
    }
    inv[n]=power(fac[n],MOD-2);
    for(int i=n-1;i>=1;i--){
        inv[i]=(inv[i+1]*(i+1))%MOD;
    }
}

void build(){
    int top=0;
    for(int i=1;i<=n;i++){
        int pos=top;
        while(pos&&val[st[pos]]>val[i]){
            pos--;
        }
        if(pos){
            rs[st[pos]]=i;
        }
        if(pos<top){
            ls[i]=st[pos+1];
        }
        st[++pos]=i;
        top=pos;
    }
}

int comb(int a,int b){
    return fac[a]*inv[b]%MOD*inv[a-b]%MOD;
}

void dfs(int u,int d){
    // cout<<u<<":  "<<ls[u]<<' '<<rs[u]<<endl;
    sz[u]=1;
    if(ls[u]){
        dfs(ls[u],d+1);
        sz[u]+=sz[ls[u]];
    }
    if(rs[u]){
        dfs(rs[u],d+1);
        sz[u]+=sz[rs[u]];
    }
    // cout<<u<<":       "<<d<<' '<<sz[u]<<' '<<(d+sz[u]-1)<<endl;
    ans=(ans+comb(d+sz[u]-1,d))%MOD;
}

signed main()
{
    prepare(2*MAXN-1);
    int T;
    T=read();
    while(T--){
        n=read();
        for(int i=1;i<=n;i++){
            val[i]=read();
            ls[i]=0,rs[i]=0;
        }
        build();
        ans=1;
        dfs(st[1],1);
        ans=(ans%MOD+MOD)%MOD;
        cout<<ans<<endl;
    }
    return 0;
}