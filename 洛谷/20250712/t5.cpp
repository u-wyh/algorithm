#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 3005;
const int LIMIT = 15;

int n,p;

int dep[MAXN];
int st[MAXN][LIMIT];

double g[MAXN];
int f[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int a[MAXN];
int b[MAXN];

int leaf[MAXN];
int len;

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

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

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

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    g[u]+=g[fa];
    f[u]=(a[u]*b[u])%MOD;
    f[u]=(f[u]+f[fa])%MOD;
    bool son=false;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs(v,u);
        son=true;
    }
    if(!son){
        leaf[++len]=u;
    }
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=p;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }
    for(int i=p;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}


signed main()
{
    n=read();
    p=log2(n)+1;
    for(int i=1;i<=n;i++){
        a[i]=read();
    }
    for(int i=1;i<=n;i++){
        b[i]=read();
        g[i]=1.0*a[i]/b[i];
        b[i]=power(b[i],MOD-2);
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++){
        double ans=INT_MAX;
        int res=INT_MAX;
        for(int j=1;j<=cnt;j++){
            int fa=lca(i,leaf[j]);
            if((g[i]+g[leaf[j]]-g[fa])<ans){
                ans=(g[i]+g[leaf[j]]-g[fa]);
                res=(f[i]+f[leaf[i]]-f[fa])%MOD;
            }
        }
        res=(res+MOD)%MOD;
        cout<<res<<endl;
    }
    return 0;
}