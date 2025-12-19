#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 1e3+5;

int n;
int sz[MAXN];
int f[MAXN][MAXN];
int comb[MAXN][MAXN];
int temp[MAXN][MAXN];
int pre[MAXN];
int suf[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void compute(int x,int y,int op){
    pre[0]=0;
    for(int i=1;i<=sz[y];i++){
        pre[i]=(pre[i-1]+f[y][i])%MOD;
    }
    suf[sz[y]+1]=0;
    for(int i=sz[y];i>=1;i--){
        suf[i]=(suf[i+1]+f[y][i])%MOD;
    }
    for(int i=1;i<=sz[x]+sz[y];i++){
        temp[x][i]=0;
    }
    for(int i=1;i<=sz[x];i++){
        for(int j=0;j<=sz[y];j++){
            long long tmp;
            if(op==1){
                tmp=pre[j];
            }
            else{
                tmp=suf[j+1];
            }
            tmp=(tmp*f[x][i])%MOD;
            tmp=(tmp*comb[i+j-1][i-1])%MOD;
            tmp=(tmp*comb[sz[x]+sz[y]-i-j][sz[x]-i])%MOD;
            temp[x][i+j]=(temp[x][i+j]+tmp)%MOD;
        }
    }
    sz[x]+=sz[y];
    for(int i=1;i<=sz[x];i++){
        f[x][i]=temp[x][i];
    }
}

void dfs(int u,int fa){
    sz[u]=1;
    f[u][1]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=fa){
            dfs(v,u);
            compute(u,v,w);
        }
    }
}

signed main()
{
    for(int i=0;i<=1000;i++){
        comb[i][0]=1;
        for(int j=1;j<=i;j++){
            comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%MOD;
        }
    }
    int T;
    scanf("%lld",&T);
    while(T--){
        scanf("%lld",&n);
        cnt=1;
        for(int i=1;i<=n;i++){
            sz[i]=0;
            head[i]=0;
            for(int j=1;j<=n;j++){
                f[i][j]=0;
            }
        }
        for(int i=1;i<n;i++){
            int u,v;
            char op;
            scanf("%lld %c %lld",&u,&op,&v);
            u++,v++;
            addedge(u,v,(op=='>')?1:0);
            addedge(v,u,(op=='<')?1:0);
        }
        dfs(1,0);
        int ans=0;
        for(int i=1;i<=n;i++){
            ans=(ans+f[1][i])%MOD;
        }
        cout<<ans<<endl;
    }
    return 0;
}