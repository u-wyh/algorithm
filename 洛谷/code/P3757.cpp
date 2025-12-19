#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 105;
const int MOD = 1e9+7;

int n;
char s[MAXN];
int sz[MAXN];
int f[MAXN][MAXN];
int temp[MAXN][MAXN];
int pre[MAXN];
int suf[MAXN];
int comb[MAXN][MAXN];

void compute(int x,int y){
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
            if(s[y]=='<'){
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
    for(int i=1;i<=sz[x]+sz[y];i++){
        f[x][i]=temp[x][i];
    }
}

void dfs(int u){
    sz[u]=1;
    f[u][1]=1;

    if(u*2<=n){
        dfs(u*2);
        compute(u,2*u);
    }
    if(u*2+1<=n){
        dfs(u*2+1);
        compute(u,2*u+1);
    }
}

signed main()
{
    scanf("%lld %s",&n,s+2);
    for(int i=0;i<=n;i++){
        comb[i][0]=1;
        for(int j=1;j<=i;j++){
            comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%MOD;
        }
    }
    dfs(1);
    int ans=0;
    for(int i=1;i<=n;i++){
        ans=(ans+f[1][i])%MOD;
    }
    cout<<ans<<endl;
    return 0;
}