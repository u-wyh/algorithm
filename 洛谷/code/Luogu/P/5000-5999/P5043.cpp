#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXM = 230;
const int MAXN = 55;

int n,m;

long long f[MAXN][MAXN];
int sz[MAXN];

bool vis[MAXM];
int prime[MAXN];
int cntt;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

void euler(int n){
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cntt]=i;
        }
        for(int j=1;j<=cntt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]==0){
                break;
            }
        }
    }
}

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void prepare(){
    cnt=1;
    for(int i=1;i<=n;i++){
        head[i]=0;
    }
}

void dfs1(int u,int fa,int op){
    sz[u]=1;
    f[op][u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs1(v,u,op);
        sz[u]+=sz[v];
        f[op][u]+=1ll*prime[sz[v]]*f[op][v];
        f[op][u]%=MOD;
    }
}

void dfs2(int u,int fa,int op){
    if(fa!=0){
        f[op][u]=f[op][u]+1ll*(prime[n-sz[u]]*(f[op][fa]-f[op][u]*prime[sz[u]]%MOD)%MOD)%MOD;
        f[op][u]%=MOD;
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs2(v,u,op);
    }
}

bool check(int i,int j){
    if(f[i][0]!=f[j][0]){
        return false;
    }
    for(int k=1;k<=f[i][0];k++){
        if(f[i][k]!=f[j][k]){
            return false;
        }
    }
    return true;
}

signed main()
{
    euler(MAXM-1);
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>n;
        prepare();
        f[i][0]=n;
        int root=0;
        for(int j=1;j<=n;j++){
            int u;
            cin>>u;
            if(u!=0){
                addedge(u,j);
            }
            else{
                root=j;
            }
        }
        dfs1(root,0,i);
        dfs2(root,0,i);
        for(int j=1;j<=n;j++){
            f[i][j]=(f[i][j]+MOD)%MOD;
        }
    }
    for(int i=1;i<=n;i++){
        sort(f[i]+1,f[i]+f[i][0]+1);
    }
    for(int i=1;i<=m;i++){
        int ans=i;
        for(int j=1;j<=m;j++){
            if(check(i,j)){
                ans=j;
                break;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}