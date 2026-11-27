#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e5+5;
const int MOD = 1e9+7;

int n;
int val[MAXN];
int f[MAXN][31];

int ans;

int comb[31][31];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int onecnt(int val){
    int cnt=0;
    while(val){
        if(val&1){
            cnt++;
        }
        val>>=1;
    }
    return cnt;
}

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
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

void dfs(int u,int fa){
    f[u][0]=1;
    for(int i=1;i<=30;i++){
        f[u][i]=(f[u][i-1]*val[u])%MOD;
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs(v,u);
        int one=onecnt(val[u]);
        for(int j=0;j<=one;j++){
            ans=(ans+(comb[one][j]*f[v][j])%MOD*f[u][one-j]%MOD)%MOD;
        }
        for(int j=0;j<=30;j++){
            f[u][j]=(f[u][j]+f[v][j])%MOD;
        }
    }
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=0;i<31;i++){
        comb[i][0]=1;
        for(int j=1;j<=i;j++){
            comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%MOD;
        }
    }
    dfs(1,0);
    ans=(ans%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}